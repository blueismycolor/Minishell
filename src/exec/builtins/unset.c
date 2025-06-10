/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:57:05 by mgodefro          #+#    #+#             */
/*   Updated: 2025/06/10 16:12:08 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Cherche l'index en comparant le nom de celle
recherchée avec celles dans env. */
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
	int		index;

	data->return_value = 0;
	if (!data->cmd->args[1])
		return ;
	if (data->cmd->args[2])
		error(data, "unset: too many arguments.", 1);
	index = get_index(data->cmd->args[1], data->env);
	if (index != -1)
		remove_var(index, data->env);
}
