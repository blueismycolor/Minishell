/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximegdfr <maximegdfr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:11:12 by mgodefro          #+#    #+#             */
/*   Updated: 2025/06/14 19:13:19 by maximegdfr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pwd(t_data *data)
{
	data->return_value = 0;
	if (data->cmd->args[1])
		return (error(data, "pwd: too many arguments.", 1));
	else
	{
		data->pwd = getcwd(NULL, 0);
		if (!data->pwd)
			error(data, "pwd: error: getcwd can't \
access parent directories.", 1);
		printf("%s\n", data->pwd);
	}
}
