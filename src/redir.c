/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:21:36 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/06/02 17:32:18 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_redir(t_data *data, t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == INPUT)
			handle_input(cmd);
		else if (redir->type == TRUNC)
			handle_trunc(cmd);
		else if (redir->type == APPEND)
			handle_append(cmd);
		else if (redir->type == HEREDOC)
		{
			cmd->fd = handle_heredoc(data, redir->filename);
			if (cmd->fd == -1)
				return ;
			if (dup2(cmd->fd, STDIN_FILENO) == -1)
				perror("dup2");
			close(cmd->fd);
		}
		redir = redir->next;
	}
}

void	handle_input(t_cmd *cmd)
{
	cmd->fd = open(cmd->redir->filename, O_RDONLY);
	if (cmd->fd == -1)
	{
		perror(cmd->redir->filename);
		return ;
	}
	if (dup2(cmd->fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(cmd->fd);
		return ;
	}
	close(cmd->fd);
}

void	handle_trunc(t_cmd *cmd)
{
	cmd->fd = open(cmd->redir->filename,
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (cmd->fd == -1)
	{
		perror(cmd->redir->filename);
		return ;
	}
	if (dup2(cmd->fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(cmd->fd);
		return ;
	}
	close(cmd->fd);
}

void	handle_append(t_cmd *cmd)
{
	cmd->fd = open(cmd->redir->filename,
			O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (cmd->fd == -1)
	{
		perror(cmd->redir->filename);
		return ;
	}
	if (dup2(cmd->fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(cmd->fd);
		return ;
	}
	close(cmd->fd);
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
