/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:10:35 by mgodefro          #+#    #+#             */
/*   Updated: 2025/08/15 12:20:02 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_n_option(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	if (arg[1] != 'n')
		return (0);
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

void	handle_echo(t_data *data)
{
	int	i;
	int	has_n;
	int	first;
	int	arglen;

	i = 1;
	has_n = 0;
	data->return_value = 0;
	while (data->cmd->args[i] && is_n_option(data->cmd->args[i]))
	{
		has_n = 1;
		i++;
	}
	first = 1;
	while (data->cmd->args[i])
	{
		if (!first)
			write(STDOUT_FILENO, " ", 1);
		arglen = ft_strlen(data->cmd->args[i]);
		write(STDOUT_FILENO, data->cmd->args[i], arglen);
		i++;
		first = 0;
	}
	if (!has_n)
		write(STDOUT_FILENO, "\n", 1);
}
