/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:46:04 by tlair             #+#    #+#             */
/*   Updated: 2025/07/02 15:43:09 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tcmd_until_last(t_cmd *list, t_cmd *cmd)
{
	t_cmd	*temp;

	while (list != cmd)
	{
		temp = list;
		list = list->next;
		if (temp->args)
			free_tab(temp->args);
		if (temp->has_redir == true)
			free_redir(temp->redir);
		free(temp);
	}
}

static void	child_pipe(t_data *data, t_cmd *cmd, int in_fd, int *pipefd)
{
	int	temp_return_value;

	close(data->saved_stdin);
	close(data->saved_stdout);
	dup2(in_fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	free_tcmd_until_last(data->cmd, cmd);
	data->cmd = cmd;
	if (handle_redir(data, cmd))
	{
		if (cmd->is_builtin)
		select_builtin(data);
		else
		{
			free(data->pids);
			process(data, cmd); // process a la place de execute_command
		}
	}
	temp_return_value = data->return_value;
	free_for_exit(data);
	exit(temp_return_value);
	}
	
	
static void	child_last(t_data *data, t_cmd *cmd, int in_fd)
{
	int	temp_return_value;

	close(data->saved_stdin);
	close(data->saved_stdout);
	dup2(in_fd, STDIN_FILENO);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	free_tcmd_until_last(data->cmd, cmd); 
	data->cmd = cmd;
	if (handle_redir(data, cmd))
	{
		if (cmd->is_builtin)
			select_builtin(data);
		else
		{
			free(data->pids);
			process(data, cmd); // process a la place de execute_command
		}
	}
	temp_return_value = data->return_value;
	free_for_exit(data);
	exit(temp_return_value);
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
	int	last_status;

	i = 0;
	while (i < data->nb_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (i == data->nb_cmds - 1)
			last_status = status;
		i++;
	}
	if (WIFSIGNALED(status))
		cat_err_handling(status, data);
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
