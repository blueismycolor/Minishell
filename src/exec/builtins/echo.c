/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:10:35 by mgodefro          #+#    #+#             */
/*   Updated: 2025/05/30 14:29:12 by tlair            ###   ########.fr       */
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

	i = 1;
	has_n = 0;
	// if (data->cmd->args[1] && ft_strcmp(data->cmd->args[1], "$?") == 0 
	// 	&& !data->cmd->args[2]) //Temp support for echo $? to print the exit code
	// {
	// 	printf("%d\n", data->return_value);
	// 	data->return_value = 0;
	// 	return;
	// }
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
			printf(" ");
		printf("%s", data->cmd->args[i]);
		i++;
		first = 0;
	}
	if (!has_n)
		printf("\n");
}
