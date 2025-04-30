/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:11:12 by mgodefro          #+#    #+#             */
/*   Updated: 2025/04/30 14:58:41 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pwd(t_data *data)
{
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
		msg_error("pwd: error: getcwd can't access parent directories.\n");
	printf("%s\n", data->pwd);
}
