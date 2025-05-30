/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:03:26 by mgodefro          #+#    #+#             */
/*   Updated: 2025/05/16 16:49:02 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error(t_data *data, char *msg, int error_code)
{
	msg_error(msg);
	data->return_value = error_code;
}

void	msg_error(char *msg)
{
	if (msg && *msg)
	{
		ft_putstr_fd("\033[1;31mError: \033[0m", 2);
		ft_putstr_fd(msg, 2);
	}
	else
		ft_putstr_fd("\033[1;31mUnknown error (ಥ﹏ಥ)\033[0m", 2);
}
