/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:26:16 by mgodefro          #+#    #+#             */
/*   Updated: 2025/07/02 18:10:17 by mgodefro         ###   ########.fr       */
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
	if (!data->env)
		return (NULL);
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
	data->env = copy_env(data, environ);
	data->history = NULL;
	data->pwd = ft_strdup(getenv("PWD"));
	if (!data->pwd)
		msg_error(ERR_MALLOC);
	data->old_pwd = NULL;
	data->return_value = 0;
	data->saved_stdin = 0;
	data->saved_stdout = 0;
	data->nb_cmds = 0;
	data->is_exit = false;
	data->pids = NULL;
	return (data);
}

// t_cmd	*init_cmd(t_cmd *cmd, char *input)
// {
// 	cmd = malloc(sizeof(t_cmd));
// 	if (!cmd)
// 		msg_error(ERR_MALLOC);
// 	cmd->cmd = ft_strdup(input);
// 	cmd->is_builtin = false;
// 	cmd->has_redir = false;
// 	cmd->redir = malloc(sizeof(t_redir));
// 	if (!cmd->redir)
// 		msg_error(ERR_MALLOC);
// 	cmd->nb_params = 0;
// 	cmd->quote = NONE;
// 	cmd->next = NULL;
// 	cmd->prev = NULL;
// 	return (cmd);
// }

t_redir	*init_redir(t_redir *redir)
{
	redir = malloc(sizeof(t_redir));
	if (!redir)
		msg_error(ERR_MALLOC);
	redir->filename = NULL;
	redir->type = CMD;
	redir->fd = -1;
	redir->next = NULL;
	return (redir);
}
