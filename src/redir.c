/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:21:36 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/05/27 15:29:58 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_redir(t_cmd *cmd)
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
			cmd->fd = create_heredoc(redir->filename);
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


int	create_heredoc(char	*del)
{
	int		fd[2];
	char	*line;
	size_t	len;

	if (pipe(fd) == -1)
		return (perror("dup2"), -1);
	line = NULL;
	len = 0;
	while (1)
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		printf("heredoc> ");
		if (getline(&line, &len, stdin) == -1)
			break ;
		if (is_delimiter(line, del))
			break ;
		write(fd[1], line, ft_strlen(line));
	}
	close(fd[1]);
	free(line);
	return (fd[0]);
}

int	is_delimiter(char *line, char *del)
{
	size_t	len;

	len = ft_strlen(del);
	return (ft_strncmp(line, del, len) == 0 && line[len] == '\n');
}

void	reset_fd(t_data *data)
{
//	if (data->cmd->fd)
//		close(data->cmd->fd);
	dup2(data->saved_stdin, STDIN_FILENO);
	dup2(data->saved_stdout, STDOUT_FILENO);
	close(data->saved_stdin);
	close(data->saved_stdout);
}