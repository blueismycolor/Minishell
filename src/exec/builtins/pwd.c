/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:11:12 by mgodefro          #+#    #+#             */
/*   Updated: 2025/08/15 14:52:27 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pwd(t_data *data)
{
	char	*cwd;
	char	*pwd_env;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
		data->return_value = 0;
		return ;
	}
	pwd_env = getenv("PWD");
	if (pwd_env)
	{
		printf("%s\n", pwd_env);
		data->return_value = 0;
		return ;
	}
	msg_error("pwd: getcwd can't access parent directories.");
	data->return_value = 1;
}
