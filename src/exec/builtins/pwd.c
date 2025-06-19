/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:11:12 by mgodefro          #+#    #+#             */
/*   Updated: 2025/06/19 13:35:16 by egatien          ###   ########.fr       */
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
