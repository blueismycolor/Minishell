/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:46:04 by tlair             #+#    #+#             */
/*   Updated: 2025/06/10 15:50:07 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	child_pipe(t_data *data, t_cmd *cmd, int in_fd, int *pipefd)
{
	dup2(in_fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	data->cmd = cmd;
	handle_redir(data, cmd);
	execute_command(data, cmd);
	exit(data->return_value);
}

static void	child_last(t_data *data, t_cmd *cmd, int in_fd)
{
	dup2(in_fd, STDIN_FILENO);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	data->cmd = cmd;
	handle_redir(data, cmd);
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

static void	wait_last(pid_t last_pid, t_data *data)
{
	int	status;

	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		data->return_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->return_value = 128 + WTERMSIG(status);
}

void	handle_pipes(t_data *data)
{
	int		pipefd[2];
	pid_t	last_pid;
	int		in_fd;
	t_cmd	*cmd;
	pid_t	pid;

	in_fd = STDIN_FILENO;
	cmd = data->cmd;
	while (cmd->next)
	{
		if (pipe(pipefd) == -1)
			return (msg_error(ERR_PIPE));
		pid = fork();
		if (pid == 0)
			child_pipe(data, cmd, in_fd, pipefd);
		parent_pipe(pid, &last_pid, &in_fd, pipefd);
		cmd = cmd->next;
	}
	pid = fork();
	if (pid == 0)
		child_last(data, cmd, in_fd);
	last_pid = pid;
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	wait_last(last_pid, data);
}
