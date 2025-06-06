/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:23:51 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/06/06 18:16:37 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*generate_heredoc_filename(void)
{
	static int	heredoc_count = 0;
	char		*count_str;
	char		*filename;
	int			len;

	count_str = ft_itoa(heredoc_count++);
	if (!count_str)
		return (NULL);

	// ".heredoc_" + chiffre + ".tmp" + '\0'
	len = strlen(".heredoc_") + strlen(count_str) + strlen(".tmp") + 1;
	filename = malloc(len);
	if (!filename)
	{
		free(count_str);
		return (NULL);
	}
	ft_strcpy(filename, ".heredoc_");
	ft_strcat(filename, count_str);
	ft_strcat(filename, ".tmp");
	free(count_str);
	return (filename);
}

static void	sigint_handler_heredoc(int sig)
{
	g_signal = sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	read_heredoc_content(int fd, char *del)
{
	char	*line;

	signal(SIGINT, sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("warning: here-document delimited by end-of-file", 2);
			ft_putstr_fd(" (wanted `", 2);
			ft_putstr_fd(del, 2);
			ft_putstr_fd("')\n", 2);
			break ;
		}
		if (ft_strcmp(line, del) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (1);
}

int	is_delimiter(char *line, char *del)
{
	size_t	len;

	len = ft_strlen(del);
	return (ft_strncmp(line, del, len) == 0 && line[len] == '\n');
}
