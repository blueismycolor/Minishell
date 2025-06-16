/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_preprocess.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:04:11 by tlair             #+#    #+#             */
/*   Updated: 2025/06/16 18:40:13 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	fill_one_heredoc(t_data *data)
{
	int		fd;
	int		status;
	int		pid;

	printf("Delimiter: %s\n", data->cmd->redir->del);
	printf("Filename: %s\n", data->cmd->redir->filename);
	fd = open(data->cmd->redir->filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		read_heredoc_content(fd, data->cmd->redir->del);
		close(fd);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	close(fd);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		data->return_value = 130;
		unlink(data->cmd->redir->filename);
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
		redir = data->cmd->redir;
		while (redir)
		{
			printf("Type: %d, Delimiter: %s, Filename: %s\n",
				redir->type, redir->del, redir->filename);
			if (redir->type == HEREDOC)
			{
				if (!fill_one_heredoc(data))
					return (0);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (1);
}
