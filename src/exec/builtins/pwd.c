/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:11:12 by mgodefro          #+#    #+#             */
/*   Updated: 2025/05/30 14:34:33 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pwd(t_data *data)
{
	data->return_value = 0;
	if (data->cmd->args[1])
		error(data, "pwd: too many arguments.\n", 1);
	else
	{
		data->pwd = getcwd(NULL, 0);
		if (!data->pwd)
			error(data, "pwd: error: getcwd can't \
access parent directories.\n", 1);
		printf("%s\n", data->pwd);
	}
}
