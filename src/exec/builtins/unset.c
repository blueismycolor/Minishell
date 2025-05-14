/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:57:05 by mgodefro          #+#    #+#             */
/*   Updated: 2025/05/14 12:39:54 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Verifier et ajouter la mise à jour du code d'erreur à renvoyer
** lors de l'execution de cette fonction.
*/

/* Cherche l'index en comparant le nom de celle recherchée avec celles dans env. */
int	get_index(char *var_name, char **env)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		if ((int)j == len && ft_strncmp(env[i], var_name, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

/* Remplace les paramètres de la variable par les nouveaux. */
void	remove_var(int var_index, char **env)
{
	int	i;

	i = var_index;
	if (env[i])
		free(env[i]);
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
}

void	handle_unset(t_data *data)
{
//	printf("ENTRY HANDLE_UNSET\n");
	int		index;

	if (!data->cmd->args[1])
		return ;
	if (data->cmd->args[2])
		msg_error("unset: too many arguments.\n");
	index = get_index(data->cmd->args[1], data->env);
	if (index != -1)
		remove_var(index, data->env);
}
