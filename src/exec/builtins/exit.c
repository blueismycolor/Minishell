/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:33:56 by mgodefro          #+#    #+#             */
/*   Updated: 2025/07/02 15:37:06 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
		if (str[i] < '0' || str[i++] > '9')
			return (0);
	return (1);
}

int	handle_exit(t_data *data)
{
	if (data->cmd->args[1] && data->cmd->args[2])
	{
		error(data, "minishell: exit: too many arguments", 1);
		return (1);
	}
	if (data->cmd->args[1])
	{
		if (!is_numeric(data->cmd->args[1]))
			error(data, "minishell: exit: numeric argument required", 2);
		else
			data->return_value = (unsigned char)ft_atoi(data->cmd->args[1])
				% 256;
	}
	close(data->saved_stdin);
	close(data->saved_stdout);
	printf("exit\n\033[1;31m(╯°□°)╯︵ ┻━┻\033[0m\n");
	data->is_exit = true;
	return (0);
}

int	handle_exit_sig(t_data *data, char *input)
{
	if (g_signal == SIGINT)
	{
		if (data->nb_cmds <= 1)
			data->return_value = 130;
		g_signal = 0;
	}
	else if (!input)
	{
		close(data->saved_stdin);
		close(data->saved_stdout);
		printf("exit\n\033[1;31m(╯°□°)╯︵ ┻━┻\033[0m\n");
		data->is_exit = true;
		return (1);
	}
	return (0);
}
