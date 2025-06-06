/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:21:36 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/06/06 18:10:47 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool handle_redir(t_data *data, t_cmd *cmd)
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
		}
		if (cmd->fd == -1)
			return (false);
		redir = redir->next;
	}
	return (true);
}

void	handle_input(t_data *data)
{
	data->cmd->fd = open(data->cmd->redir->filename, O_RDONLY);
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
	data->cmd->fd = open(data->cmd->redir->filename,
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
	data->cmd->fd = open(data->cmd->redir->filename,
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

void	reset_fd(t_data *data)
{
	if (!data->is_exit)
	{
		dup2(data->saved_stdin, STDIN_FILENO);
		dup2(data->saved_stdout, STDOUT_FILENO);
		close(data->saved_stdin);
		close(data->saved_stdout);
	}
}
