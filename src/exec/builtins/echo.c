/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:10:35 by mgodefro          #+#    #+#             */
/*   Updated: 2025/05/16 16:54:45 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Verifier et ajouter la mise à jour du code d'erreur à renvoyer
** lors de l'execution de cette fonction.
*/

#include "../includes/minishell.h"

int	is_n_option(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	if (arg[1] != 'n')
		return (0);
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0'); // Si *arg fini par NULL = 1 (true) / Sinon, 0 (false)
}

void	handle_echo(t_data *data)
{
//	printf("ENTRY HANDLE_ECHO\n");
	int	i;
	int	has_n;
	int	first;

	data->return_value = 0;
	i = 1;
	has_n = 0;
	while (data->cmd->args[i] && is_n_option(data->cmd->args[i]))
	{
		has_n = 1;
		i++;
	}
	first = 1;
	while (data->cmd->args[i])
	{
		if (!first)
			printf(" ");
		printf("%s", data->cmd->args[i]);
		i++;
		first = 0;
	}
	if (!has_n)
		printf("\n");
}
