/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:26:16 by mgodefro          #+#    #+#             */
/*   Updated: 2025/04/30 15:09:07 by mgodefro         ###   ########.fr       */
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
	data->cmd = NULL;
	data->env = copy_env(data, environ);
	data->historic = NULL;
	data->old_pwd = getenv("PWD");
	data->pwd = getenv("PWD");
	data->return_value = 0;
	return (data);
}

t_cmd	*init_cmd(t_cmd *cmd, char *input)
{
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		msg_error(ERR_MALLOC);
	cmd->cmd = input;
	cmd->args = NULL;
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
