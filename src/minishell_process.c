/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:30:05 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/06/02 17:50:36 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pipes(t_data *data)
{
	int		in_fd = STDIN_FILENO;
	int		pipefd[2];
	pid_t	pid[128];
	int		i;

	i = 0;
	if (!data->cmd)
		return ;
	while (data->cmd->next)
	{
		printf("current cmd : %p\n", data->cmd);
		printf("next cmd : %p\n", data->cmd->next);
		if (pipe(pipefd) == -1)
		{
			msg_error(ERR_PIPE);
			return ;
		}
		if ((pid[i] = fork()) == 0)
		{
			if (in_fd != STDIN_FILENO)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			handle_redir(data, data->cmd);
			if (data->cmd->is_builtin)
				select_builtin(data);
			else
				execute_command(data);
			exit(EXIT_SUCCESS);
		}
		close(pipefd[1]);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		in_fd = pipefd[0];
		data->cmd = data->cmd->next;
		i++;
	}
	if ((pid[i] = fork()) == 0)
	{
		if (in_fd != STDIN_FILENO)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		handle_redir(data, data->cmd);
		if (data->cmd->is_builtin)
			select_builtin(data);
		else
			execute_command(data);
		exit(EXIT_SUCCESS);
	}
	if (in_fd != STDIN_FILENO)
		close(in_fd);

	int j = 0;
	while (j <= i)
	{
		waitpid(pid[j], NULL, 0);
		j++;
	}
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
