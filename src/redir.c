/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximegdfr <maximegdfr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:21:36 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/06/10 16:57:19 by maximegdfr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	handle_heredoc_redir(t_cmd *cmd, t_redir *redir)
{
	cmd->fd = open(redir->filename, O_RDONLY);
	if (cmd->fd == -1)
		return (false);
	if (dup2(cmd->fd, STDIN_FILENO) == -1)
	{
		close(cmd->fd);
		return (false);
	}
	close(cmd->fd);
	unlink(redir->filename);
	free(redir->filename);
	redir->filename = NULL;
	return (true);
}

bool	handle_redir(t_data *data, t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == INPUT)
			handle_input(data);
		else if (redir->type == TRUNC)
			handle_trunc(data);
		else if (redir->type == APPEND)
			handle_append(data);
		else if (redir->type == HEREDOC)
		{
			if (!handle_heredoc_redir(cmd, redir))
				return (false);
		}
		if (cmd->fd == -1)
			return (false);
		redir = redir->next;
	}
	return (true);
}

void	handle_input(t_data *data)
{
	data->cmd->fd = open(data->cmd->redir->del, O_RDONLY);
	if (data->cmd->fd == -1)
	{
		error(data, data->cmd->redir->filename, 1);
		return ;
	}
	if (dup2(data->cmd->fd, STDIN_FILENO) == -1)
	{
		error(data, "dup2", 1);
		close(data->cmd->fd);
		return ;
	}
	close(data->cmd->fd);
}

void	handle_trunc(t_data *data)
{
	data->cmd->fd = open(data->cmd->redir->del,
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data->cmd->fd == -1)
	{
		error(data, data->cmd->redir->filename, 1);
		return ;
	}
	if (dup2(data->cmd->fd, STDOUT_FILENO) == -1)
	{
		error(data, "dup2", 1);
		close(data->cmd->fd);
		return ;
	}
	close(data->cmd->fd);
}

void	handle_append(t_data *data)
{
	data->cmd->fd = open(data->cmd->redir->del,
			O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (data->cmd->fd == -1)
	{
		error(data, data->cmd->redir->filename, 1);
		return ;
	}
	if (dup2(data->cmd->fd, STDOUT_FILENO) == -1)
	{
		error(data, "dup2", 1);
		close(data->cmd->fd);
		return ;
	}
	close(data->cmd->fd);
}
