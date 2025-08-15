/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:09:59 by tlair             #+#    #+#             */
/*   Updated: 2025/07/04 12:02:04 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	char	*result;

	if (!s1 || !s2 || !s3)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, s3);
	free(tmp);
	return (result);
}

void	free_tcmd_until_last(t_cmd *list, t_cmd *cmd)
{
	t_cmd	*temp;

	while (list != cmd)
	{
		temp = list;
		list = list->next;
		if (temp->args)
			free_tab(temp->args);
		if (temp->has_redir == true)
			free_redir(temp->redir);
		free(temp);
	}
}

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
