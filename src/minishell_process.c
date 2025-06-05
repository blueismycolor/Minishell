/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:30:05 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/06/03 18:05:13 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	open_all_heredocs(t_data *data)
{
	t_redir	*redir = data->cmd->redir;

	while (redir)
	{
		if (redir->type == HEREDOC)
			handle_heredoc(data, redir->filename, redir->del);
		redir = redir->next;
	}
}

void handle_pipes(t_data *data)
{
	int pipefd[2];
	pid_t last_pid;
	int status;
	int in_fd = STDIN_FILENO;

	while (data->cmd->next)
	{
		open_all_heredocs(data);
		pipe(pipefd);
		pid_t pid = fork();
		if (pid == 0)
		{
			dup2(in_fd, STDIN_FILENO);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]);
			handle_redir(data);
			execute_command(data);
			exit(data->return_value);
		}
		else
		{
			last_pid = pid; 
			close(pipefd[1]);
			if (in_fd != STDIN_FILENO) close(in_fd);
			in_fd = pipefd[0];
			data->cmd = data->cmd->next;
		}
	}
    pid_t pid = fork();
    if (pid == 0)
    {
        dup2(in_fd, STDIN_FILENO);
        handle_redir(data);
        execute_command(data);
        exit(data->return_value);
    }
    else
    {
        last_pid = pid;
        close(in_fd);
    }
    waitpid(last_pid, &status, 0);
    if (WIFEXITED(status))
        data->return_value = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        data->return_value = 128 + WTERMSIG(status);
}

int	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		msg_error(ERR_PIPE);
		return (-1);
	}
	return (0);
}

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		msg_error(ERR_FORK);
	return (pid);
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
