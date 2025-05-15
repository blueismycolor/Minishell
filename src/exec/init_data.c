/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:26:16 by mgodefro          #+#    #+#             */
/*   Updated: 2025/05/15 17:03:50 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**copy_env(t_data *data, char **environ)
{
	int	i;
	int	count;

	count = 0;
	while (environ[count])
		count++;
	data->env = malloc((count + 1) * sizeof(char *));
	i = 0;
	while (i < count)
	{
		data->env[i] = ft_strdup(environ[i]);
		i++;
	}
	data->env[i] = NULL;
	return (data->env);
}

t_data	*init_data(char **environ)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		msg_error(ERR_MALLOC);
	data->cmd = malloc(sizeof(t_cmd));
	if (!data->cmd)
		msg_error(ERR_MALLOC);
	data->env = copy_env(data, environ);
	data->history = NULL;
	data->pwd = ft_strdup(getenv("PWD"));
	if (!data->pwd)
		msg_error(ERR_MALLOC);
	data->old_pwd = ft_strdup(data->pwd);
	if (!data->old_pwd)
		msg_error(ERR_MALLOC);
	data->return_value = 0;
	return (data);
}

t_cmd	*init_cmd(t_cmd *cmd, char *input)
{
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		msg_error(ERR_MALLOC);
	cmd->cmd = ft_strdup(input);
	cmd->args = create_arguments(cmd);

	// Temporaire (doit etre gerer par le parsing)
	if (ft_strncmp(cmd->cmd, "cd", 2) == 0
		|| ft_strncmp(cmd->cmd, "echo", 4) == 0
		|| ft_strncmp(cmd->cmd, "env", 3) == 0
		|| ft_strncmp(cmd->cmd, "exit", 4) == 0
		|| ft_strncmp(cmd->cmd, "export", 6) == 0
		|| ft_strncmp(cmd->cmd, "pwd", 3) == 0
		|| ft_strncmp(cmd->cmd, "unset", 5) == 0)
		cmd->is_builtin = true;
	else
		cmd->is_builtin = false;

	cmd->has_redir = false;
	cmd->redir = NULL;
	cmd->nb_params = 0;
	cmd->quote = NONE;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

t_redir	*init_redir(t_redir *redir)
{
	redir = malloc(sizeof(t_redir));
	if (!redir)
		msg_error(ERR_MALLOC);
	redir->filename = NULL;
	redir->type = CMD;
	redir->next = NULL;
	return (redir);
}
