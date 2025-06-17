/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_preprocess.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:04:11 by tlair             #+#    #+#             */
/*   Updated: 2025/06/17 17:51:18 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	sigint_handler_heredoc(int sig)
{
	g_signal = sig;
	// printf("g_signal: %d\n", g_signal);
	exit(1);
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
	{
		signal(SIGINT, sigint_handler_heredoc);
		// signal(SIGQUIT, sigint_handler_heredoc);
		read_heredoc_content(fd, redir->del);
		close(fd);
		unlink(redir->filename);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	close(fd);
	signal(SIGINT, sigint_handler_heredoc);
	// signal(SIGQUIT, sigint_handler_heredoc);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		data->return_value = 130;
		close(fd);
		unlink(redir->filename);
		return (0);
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
