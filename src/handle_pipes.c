/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:46:04 by tlair             #+#    #+#             */
/*   Updated: 2025/06/19 13:30:48 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	child_pipe(t_data *data, t_cmd *cmd, int in_fd, int *pipefd)
{
	close(data->saved_stdin);
	close(data->saved_stdout);
	dup2(in_fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	data->cmd = cmd;
	handle_redir(data, cmd);
	if (cmd->is_builtin)
		select_builtin(data);
	else
		execute_command(data, cmd);
	exit(data->return_value);
}

static void	child_last(t_data *data, t_cmd *cmd, int in_fd)
{
	close(data->saved_stdin);
	close(data->saved_stdout);
	dup2(in_fd, STDIN_FILENO);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	data->cmd = cmd;
	handle_redir(data, cmd);
	if (cmd->is_builtin)
		select_builtin(data);
	else
		execute_command(data, cmd);
	exit(data->return_value);
}

static void	parent_pipe(pid_t pid, int *last_pid, int *in_fd, int *pipefd)
{
	*last_pid = pid;
	close(pipefd[1]);
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	*in_fd = pipefd[0];
}

static void	wait_all(pid_t *pids, t_data *data)
{
	int	status;
	int	i;

	i = 0;
	while (i < data->nb_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (i == data->nb_cmds - 1)
		{
			if (WIFEXITED(status))
				data->return_value = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->return_value = 128 + WTERMSIG(status);
		}
		i++;
	}
	free(data->pids);
}

void	handle_pipes(t_data *data)
{
	int		pipefd[2];
	int		i;
	int		in_fd;
	t_cmd	*cmd;

	in_fd = STDIN_FILENO;
	cmd = data->cmd;
	i = 0;
	while (cmd->next)
	{
		if (pipe(pipefd) == -1)
			return (msg_error(ERR_PIPE));
		data->pids[i] = fork();
		if (data->pids[i] == 0)
			child_pipe(data, cmd, in_fd, pipefd);
		parent_pipe(data->pids[i], &data->pids[data->nb_cmds - 1], &in_fd, pipefd);
		cmd = cmd->next;
		i++;
	}
	data->pids[i] = fork();
	if (data->pids[i] == 0)
		child_last(data, cmd, in_fd);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	wait_all(data->pids, data);
}
