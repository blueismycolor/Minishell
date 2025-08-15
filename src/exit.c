/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:03:26 by mgodefro          #+#    #+#             */
/*   Updated: 2025/07/02 15:39:14 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	update_return_value(t_data *data, int value)
{
	if (value < 0 || value > 255)
		data->return_value = 1;
	else
		data->return_value = value;
	return (data->return_value);
}

void	error(t_data *data, char *msg, int error_code)
{
	msg_error(msg);
	data->return_value = error_code;
}

void	msg_error(char *msg)
{
	if (msg && *msg)
	{
		if (ft_strcmp(msg, ERR_HEREDOC) == 0)
		{
			ft_putstr_fd("warning: here-document delimited by end-of-file", 2);
			ft_putstr_fd(" (wanted '", 2);
		}
		else if (ft_strcmp(msg, ERR_CMD_NOT_FOUND) == 0)
			ft_putstr_fd("\033[1;31mminishell: command not found: \033[0m", 2);
		else
		{
			ft_putstr_fd("\033[1;31mError: \033[0m", 2);
			ft_putstr_fd(msg, 2);
			ft_putstr_fd("\n", 2);
		}
	}
	else
		ft_putstr_fd("\033[1;31mUnknown error (ಥ﹏ಥ)\033[0m\n", 2);
}

void	cat_err_handling(int status, t_data *data)
{
	int	sig;

	sig = WTERMSIG(status);
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		data->return_value = 130;
	}
	else if (sig == SIGQUIT)
	{
		if (WCOREDUMP(status))
			write(2, "Quit (core dumped)\n", 19);
		else
			write(2, "Quit\n", 5);
		data->return_value = 131;
	}
}
