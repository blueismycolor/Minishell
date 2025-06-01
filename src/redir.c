/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:21:36 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/05/30 15:40:13 by tlair            ###   ########.fr       */
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
			if (g_signal || cmd->fd == -1)
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

void heredoc_sigint_handler(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
}

int create_heredoc(char *del)
{
	int		fd[2];
	char	*line = NULL;
	size_t	len = 0;
	struct	sigaction sa_old, sa_new;

	sa_new.sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa_new.sa_mask);
	sa_new.sa_flags = 0;
	sigaction(SIGINT, &sa_new, &sa_old);
	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	while (!g_signal)
	{
		printf("heredoc> ");
		if (getline(&line, &len, stdin) == -1)
			break ;
		if (g_signal || is_delimiter(line, del))
			break ;
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = NULL;
	}
	close(fd[1]);
	free(line);
	sigaction(SIGINT, &sa_old, NULL);
	if (g_signal)
	{
		close(fd[0]);
		g_signal = 0;
		return (-1);
	}
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
	if (!data->is_exit)
	{
		dup2(data->saved_stdin, STDIN_FILENO);
		dup2(data->saved_stdout, STDOUT_FILENO);
		close(data->saved_stdin);
		close(data->saved_stdout);
	}
}
