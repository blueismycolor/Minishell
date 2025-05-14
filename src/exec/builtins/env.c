/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:44:54 by mgodefro          #+#    #+#             */
/*   Updated: 2025/05/14 12:38:45 by mgodefro         ###   ########.fr       */
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

	if (data->cmd->args[1] != NULL)
	{
		msg_error("env: too many arguments.\n");
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

