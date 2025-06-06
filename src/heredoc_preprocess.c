/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_preprocess.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:04:11 by tlair             #+#    #+#             */
/*   Updated: 2025/06/06 17:06:27 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	fill_one_heredoc(t_redir *redir)
{
	int	fd;
	int	status;

	if (redir->type != HEREDOC)
		return (1);
	fd = open(redir->filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (0);
	status = read_heredoc_content(fd, redir->del);
	close(fd);
	return (status);
}

int	preprocess_heredocs(t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				if (!fill_one_heredoc(redir))
					return (0);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (1);
}
