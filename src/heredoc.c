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

int	handle_heredoc(t_data *data, char *filename, char *del)
{
	int		fd;

	data->return_value = 0;
	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (-1);
	if (!read_in_stdin(fd, del))
	{
		unlink(filename);
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd > 0)
		unlink(filename);
	return (fd);
}

int	is_delimiter(char *line, char *del)
{
	size_t	len;

	len = ft_strlen(del);
	return (ft_strncmp(line, del, len) == 0 && line[len] == '\n');
}
