/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:30:05 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/07/04 11:21:28 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_command(t_data *data, t_cmd *cmd)
{
	pid_t		pid;
	int			status;

	status = 0;
	pid = fork();
	if (pid == 0)
		process(data, cmd);
	else if (pid > 0)
		exit_process(data, pid, status);
}

void	execute_commands(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	data->nb_cmds = 0;
	while (cmd)
	{
		data->nb_cmds++;
		cmd = cmd->next;
	}
	if (data->nb_cmds > 1)
	{
		data->pids = malloc(sizeof(pid_t) * data->nb_cmds);
		if (!data->pids)
			return (msg_error(ERR_MALLOC));
		handle_pipes(data);
	}
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
	if (!preprocess_heredocs(data) || preprocess_redirections(data) != 0)
		return (false);
	return (true);
}

void	select_builtin(t_data *data)
{
	if (!data->cmd || !data->cmd->cmd)
		msg_error("Invalid command.");
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
	if (ft_strncmp(data->cmd->cmd, "exit", 4) == 0)
		handle_exit(data);
}
