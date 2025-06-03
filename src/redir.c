/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:21:36 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/06/03 18:22:32 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_redir(t_data *data)
{
	while (data->cmd->redir)
	{
		if (data->cmd->redir->type == INPUT)
			handle_input(data);
		else if (data->cmd->redir->type == TRUNC)
			handle_trunc(data);
		else if (data->cmd->redir->type == APPEND)
			handle_append(data);
		else if (data->cmd->redir->type == HEREDOC)
		{
			data->cmd->fd = handle_heredoc(data, data->cmd->redir->filename);
			if (data->cmd->fd == -1)
				return ;
			if (dup2(data->cmd->fd, STDIN_FILENO) == -1)
				error(data, "dup2", 1);
			close(data->cmd->fd);
		}
		data->cmd->redir = data->cmd->redir->next;
	}
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
