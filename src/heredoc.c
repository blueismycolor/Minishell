/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:23:51 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/06/02 16:02:28 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	sigint_handler_heredoc(int sig)
{
	printf("ENTRY SIGNAL_HEREDOC\n");
	g_signal = sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

static bool	read_in_stdin(int fd, char *del)
{
	char	*buffer;

	signal(SIGINT, sigint_handler_heredoc);
	while (1)
	{
		buffer = NULL;
		if (g_signal)
			break ;
		buffer = readline("> ");
		if (!buffer)
		{
			msg_error(ERR_HEREDOC);
			break ;
		}
		if (!ft_strncmp(del, buffer, INT_MAX))
			break ;
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", sizeof(char));
		free(buffer);
	}
	free(buffer);
	close(fd);
	g_signal = 0;
	return (true);
}

int	handle_heredoc(t_data *data, char *del)
{
	int		fd;

	data->return_value = 0;
	fd = open(".heredoc.tmp", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (-1);
	if (!read_in_stdin(fd, del))
	{
		unlink(".heredoc.tmp");
		return (-1);
	}
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd > 0)
		unlink(".heredoc.tmp");
	return (fd);
}

int	is_delimiter(char *line, char *del)
{
	size_t	len;

	len = ft_strlen(del);
	return (ft_strncmp(line, del, len) == 0 && line[len] == '\n');
}
