/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:30:05 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/06/06 18:08:37 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pipes(t_data *data)
{
	int		pipefd[2];
	pid_t	last_pid;
	int		status;
	int		in_fd;
	t_cmd	*cmd;
	pid_t	pid;

	in_fd = STDIN_FILENO;
	cmd = data->cmd;
	while (cmd->next)
	{
		if (pipe(pipefd) == -1)
		{
			msg_error(ERR_PIPE);
			return ;
		}
		pid = fork();
		if (pid == 0)
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
		else
		{
			last_pid = pid;
			close(pipefd[1]);
			if (in_fd != STDIN_FILENO)
				close(in_fd);
			in_fd = pipefd[0];
			cmd = cmd->next;
		}
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(in_fd, STDIN_FILENO);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		data->cmd = cmd;
		handle_redir(data, cmd);
		execute_command(data, cmd);
		exit(data->return_value);
	}
	else
	{
		last_pid = pid;
		if (in_fd != STDIN_FILENO)
			close(in_fd);
	}
	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		data->return_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->return_value = 128 + WTERMSIG(status);
}

void	select_builtin(t_data *data)
{
	if (!data->cmd || !data->cmd->cmd)
		msg_error("Invalid command.\n");
	if (ft_strncmp(data->cmd->cmd, "cd", 2) == 0)
		handle_cd(data);
	if (ft_strncmp(data->cmd->cmd, "echo", 4) == 0)
		handle_echo(data);
	if (ft_strncmp(data->cmd->cmd, "env", 3) == 0)
		handle_env(data);
	if (ft_strncmp(data->cmd->cmd, "export", 6) == 0)
		handle_export_var(data);
	if (ft_strncmp(data->cmd->cmd, "pwd", 3) == 0)
		handle_pwd(data);
	if (ft_strncmp(data->cmd->cmd, "unset", 5) == 0)
		handle_unset(data);
}
