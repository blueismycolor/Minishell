/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:11:12 by mgodefro          #+#    #+#             */
/*   Updated: 2025/05/14 12:39:38 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pwd(t_data *data)
{
//	printf("ENTRY HANDLE_PWD\n");
	if (data->cmd->args[1])
		msg_error("pwd: too many arguments.\n");
	else
	{
		data->pwd = getcwd(NULL, 0);
		if (!data->pwd)
			msg_error("pwd: error: getcwd can't access parent directories.\n");
		printf("%s\n", data->pwd);
	}
}
