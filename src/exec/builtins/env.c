/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:44:54 by mgodefro          #+#    #+#             */
/*   Updated: 2025/05/16 16:55:33 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Verifier et ajouter la mise à jour du code d'erreur à renvoyer
** lors de l'execution de cette fonction.
*/

#include "../includes/minishell.h"

void	handle_env(t_data *data)
{
//	printf("ENTRY HANDLE_ENV\n");
	int	i;

	data->return_value = 0;
	if (data->cmd->args[1] != NULL)
	{
		error(data, "env: too many arguments.\n", 1);
		return ;
	}
	else
	{
		i = 0;
		while (data->env[i])
		{
			printf("%s\n", data->env[i]);
			i++;
		}
	}
}
