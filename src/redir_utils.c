/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:04:30 by egatien           #+#    #+#             */
/*   Updated: 2025/07/04 12:09:56 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_redirections(t_redir *redir)
{
	redir->fd = -1;
	if (redir->type == INPUT)
		redir->fd = open(redir->del, O_RDONLY);
	if (redir->type == APPEND)
		redir->fd = open(redir->del, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (redir->type == TRUNC)
		redir->fd = open(redir->del, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	return (redir->fd);
}

int	preprocess_redirections(t_data *data)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = data->cmd;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == INPUT || redir->type == APPEND
				|| redir->type == TRUNC)
			{
				open_redirections(redir);
				if (redir->fd == -1)
				{
					clean_redirections(data);
					return (error(data, "Permission denied", 1), 1);
				}
				clean_redirections(data);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

void	clean_redirections(t_data *data)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = data->cmd;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->fd >= 0)
				close(redir->fd);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
