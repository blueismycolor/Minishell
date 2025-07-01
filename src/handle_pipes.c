/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:46:04 by tlair             #+#    #+#             */
/*   Updated: 2025/07/01 17:54:02 by tlair            ###   ########.fr       */
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
	if (handle_redir(data, cmd))
	{
		if (cmd->is_builtin)
			select_builtin(data);
		else
			process(data, cmd); // process a la place de execute_command
	}
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
	if (handle_redir(data, cmd))
	{
		if (cmd->is_builtin)
			select_builtin(data);
		else
			process(data, cmd); // process a la place de execute_command
	}
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

static void wait_all(pid_t *pids, t_data *data)
{
	int	status;
	int	i;
	int	last_status;
	int	sig;

	i = 0;
	sig = 0;
	while (i < data->nb_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (i == data->nb_cmds - 1)
			last_status = status;
		i++;
	}
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			write(1, "\n", 1);
			data->return_value = 130;
		}
		else if (sig == SIGQUIT)
		{
			if (WCOREDUMP(status))
				write(2, "Quit (core dumped)\n", 19);
			else
				write(2, "Quit\n", 5);
			data->return_value = 131;
		}
	}
	if (WIFEXITED(last_status))
		data->return_value = WEXITSTATUS(last_status);
	else if (WIFSIGNALED(last_status))
		data->return_value = 128 + WTERMSIG(last_status);
	free(data->pids);
}

void	handle_pipes(t_data *data)
{
	int		p_fd[2];
	int		i;
	int		in;
	t_cmd	*cmd;

	in = STDIN_FILENO;
	cmd = data->cmd;
	i = 0;
	while (cmd->next)
	{
		if (pipe(p_fd) == -1)
			return (msg_error(ERR_PIPE));
		data->pids[i] = fork();
		if (data->pids[i] == 0)
			child_pipe(data, cmd, in, p_fd);
		parent_pipe(data->pids[i], &data->pids[data->nb_cmds - 1], &in, p_fd);
		cmd = cmd->next;
		i++;
	}
	data->pids[i] = fork();
	if (data->pids[i] == 0)
		child_last(data, cmd, in);
	if (in != STDIN_FILENO)
		close(in);
	wait_all(data->pids, data);
}
