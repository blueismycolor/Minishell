/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:38:12 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/06/24 15:59:22 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Cherche l'index en comparant le nom de celle
recherchée avec celles dans env. */
int	var_index(t_data *data, char *var_name)
{
	int	i;
	int	j;

	i = 0;
	while (data->env[i])
	{
		j = 0;
		while (data->env[i][j]
			&& (data->env[i][j] == var_name[j])
			&& (var_name[j] != '\0' && var_name[j] != '=')
			&& (data->env[i][j] != '\0' && data->env[i][j] != '='))
			j++;
		if ((data->env[i][j] == '\0' || data->env[i][j] == '=')
			&& (var_name[j] == '\0' || var_name[j] == '='))
			return (i);
		i++;
	}
	return (-1);
}

/* Remplace les paramètres de la variable par les nouveaux. */
void	replace_var(t_data *data, char *new_var, int var_index)
{
	if (ft_strchr(new_var, '='))
	{
		free(data->env[var_index]);
		data->env[var_index] = ft_strdup(new_var);
	}
}

/* Tri les variables d'environnement pour les
print dans l'ordre alphabetique comme bash. */
void	export_sorted_var(t_data *data)
{
	int		i;
	int		env_len;
	char	*to_swap;
	char	**tmp_env;

	i = 0;
	env_len = get_env_len(data);
	tmp_env = malloc(sizeof(char *) * (env_len + 1));
	if (!tmp_env)
		msg_error(ERR_MALLOC);
	tmp_env = ft_memcpy(tmp_env, data->env, sizeof(char *) * (env_len + 1));
	while (tmp_env[i + 1])
	{
		if (ft_strcmp(tmp_env[i], tmp_env[i + 1]) > 0)
		{
			to_swap = tmp_env[i];
			tmp_env[i] = tmp_env[i + 1];
			tmp_env[i + 1] = to_swap;
			i = 0;
		}
		else
			i++;
	}
	print_export(tmp_env);
	free(tmp_env);
}

/* Exporte toutes les variables d'environnement (ex : "export"). */
char	**add_var_env(t_data *data, char *new_var)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (get_env_len(data) + 2));
	if (!new_env)
		msg_error(ERR_MALLOC);
	while (data->env[i])
	{
		new_env[i] = ft_strdup(data->env[i]);
		i++;
	}
	new_env[i] = ft_strdup(new_var);
	new_env[i + 1] = NULL;
	free_tab(data->env);
	return (new_env);
}

/* Permet de gérer l'export des variables d'environnement. */
void	handle_export_var(t_data *data)
{
	int		i;
	int		j;
	char	*var_name;

	data->return_value = 0;
	i = 0;
	j = 1;
	if (!data->cmd->args[1])
		return (export_sorted_var(data));
	while (data->cmd->args[j])
	{
		var_name = get_var_name(data->cmd->args[j]);
		if (!var_name)
		{
			error(data, "export: invalid variable name.", 1);
			return ;
		}
		i = var_index(data, var_name);
		if (i != -1)
			replace_var(data, data->cmd->args[j], i);
		else
			data->env = add_var_env(data, data->cmd->args[j]);
		free(var_name);
		j++;
	}
}
