/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:30:05 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/06/10 15:45:46 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_command(t_data *data, t_cmd *cmd)
{
	pid_t		pid;
	extern char	**environ;
	int			status;

	status = 0;
	pid = fork();
	if (pid == 0)
		process(data, cmd, environ);
	else if (pid > 0)
		exit_process(data, pid, status);
}

void	execute_commands(t_data *data)
{
	if (data->cmd->next)
		handle_pipes(data);
	else if (handle_redir(data, data->cmd))
	{
		if (data->cmd->is_builtin)
			select_builtin(data);
		else
			execute_command(data, data->cmd);
	}
}

bool	process_input(t_data *data, char *input)
{
	data->cmd = tcmd_init(input, data);
	if (!data->cmd && !data->is_exit)
		return (false);
	if (!preprocess_heredocs(data->cmd))
		return (false);
	return (true);
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
