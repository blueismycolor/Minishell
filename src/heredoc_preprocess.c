/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_preprocess.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:04:11 by tlair             #+#    #+#             */
/*   Updated: 2025/07/02 16:35:28 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_for_open_fd(int fd)
{
	static int	fd_temp;
	if (fd != -1)
		fd_temp = fd;
	return (fd_temp);
}

t_data	*set_for_free_data(t_data *data)
{
	static t_data	*data_temp;
	if (data != NULL)
		data_temp = data;
	return (data_temp);
}

static void	sigint_handler_heredoc(int sig)
{
	t_data	*data_temp;
	int		fd_temp;

	fd_temp = -1;
	data_temp = NULL;
	data_temp = set_for_free_data(data_temp);
	fd_temp = set_for_open_fd(fd_temp);
	g_signal = sig;
	if (sig == SIGINT)
	{
		close(fd_temp);
		close(data_temp->saved_stdin);
		close(data_temp->saved_stdout);
		if (data_temp)
		{
			free_tcmd(data_temp->cmd);
			free_data(data_temp);
		}
		exit(130);
	}
}
static void	child_heredoc(int fd, t_redir *redir, t_data *data)
{
	set_for_free_data(data);
	set_for_open_fd(fd);
	signal(SIGINT, sigint_handler_heredoc);
	read_heredoc_content(fd, redir->del);
	close(fd);
	close(data->saved_stdin);
	close(data->saved_stdout);
	free_for_exit(data);
	exit(0);
}

static int	fill_one_heredoc(t_data *data, t_redir *redir)
{
	int		fd;
	int		status;
	int		pid;

	fd = open(redir->filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (0);
	pid = fork();
	if (pid < 0)
	{
		close(fd);
		return (0);
	}
	if (pid == 0)
		child_heredoc(fd, redir, data);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	close(fd);
	signal(SIGINT, sigint_handler_heredoc);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		data->return_value = 130;
		return (close(fd), unlink(redir->filename), 0);
	}
	return (1);
}

int	preprocess_heredocs(t_data *data)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = data->cmd;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				if (!fill_one_heredoc(data, redir))
					return (0);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (1);
}

void	cleanup_heredocs(t_data *data)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = data->cmd;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == HEREDOC && redir->filename)
			{
				unlink(redir->filename);
				free(redir->filename);
				redir->filename = NULL;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
