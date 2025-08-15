/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_preprocess.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:04:11 by tlair             #+#    #+#             */
/*   Updated: 2025/07/08 16:28:03 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (WEXITSTATUS(status) == 130)
	{
		data->return_value = WEXITSTATUS(status);
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
