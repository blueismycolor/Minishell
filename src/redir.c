/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:21:36 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/07/02 17:21:51 by mgodefro         ###   ########.fr       */
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
			handle_input(data, redir);
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

void	handle_input(t_data *data, t_redir *redir)
{
	data->cmd->fd = open(redir->del, O_RDONLY);
	if (data->cmd->fd == -1)
		return (error(data, NO_PATH, 1));
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
	t_redir	*temp;

	temp = data->cmd->redir;
	while (temp->next)
		temp = temp->next;
	data->cmd->fd = open(temp->del,
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data->cmd->fd == -1)
	{
		error(data, temp->filename, 1);
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
	t_redir	*temp;

	temp = data->cmd->redir;
	while (temp->next)
		temp = temp->next;
	data->cmd->fd = open(temp->del,
			O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (data->cmd->fd == -1)
	{
		error(data, temp->filename, 1);
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

static int	open_redirections(t_redir *redir)
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
			if (redir->type == INPUT || redir->type == APPEND || redir->type == TRUNC)
			{
				if (!open_redirections(redir))
				{
					error(data, ERR_REDIR, 1);
					return (-1);
				}
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
			if (redir->fd)
				close(redir->fd);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
