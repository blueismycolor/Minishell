/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:38:12 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/04/30 15:49:02 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Verifier et ajouter la mise à jour du code d'erreur à renvoyer
** lors de l'execution de cette fonction.
*/

/*
** Doit permettre d'ajouter une variable d'environnement UNIQUEMENT si celle-ci
** a une valeur attribuee.
*/

#include "../includes/minishell.h"

/* Cherche l'index en comparant le nom de celle recherchée avec celles dans env. */
int	var_index(char *var_name, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j]
			&& (env[i][j] == var_name[j])
			&& (var_name[j] != '\0' && var_name[j] != '=')
			&& (env[i][j] != '\0' && env[i][j] != '='))
			j++;
		if ((env[i][j] == '\0' || env[i][j] == '=')
			&& (var_name[i] == '\0' || var_name[j] == '='))
			return (i);
	}
	return (-1);
}

/* Remplace les paramètres de la variable par les nouveaux. */
void	replace_var(char *new_var, int var_index, char **env)
{
	if (ft_strchr(new_var, '='))
		env[var_index] = ft_strdup(new_var);
	return ;
}

/* Tri les variables d'environnement pour les print dans l'ordre alphabetique comme bash. */
void	export_sorted_var(char **env)
{
	int		i;
	int		j;
	int		env_len;
	char	*to_swap;
	char	**tmp_env;

	i = 0;
	env_len = get_env_len(env);
	tmp_env = NULL;
	tmp_env = ft_memmove(tmp_env, env, env_len);
	while (tmp_env[i + 1])
	{
		j = i + 1;
		if (ft_strcmp(tmp_env[i], tmp_env[j]) != 0)
		{
			to_swap = tmp_env[j];
			tmp_env[j] = tmp_env[i];
			tmp_env[i] = to_swap;
			i = 0;
		}
		else
			i++;
	}
	print_export(tmp_env);
	free_tab(tmp_env);
}

/* Exporte toutes les variables d'environnement (ex : "export"). */
char	**add_var_env(char **env, char *new_var)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (get_env_len(env) + 1));
	if (!new_env)
		msg_error(ERR_MALLOC);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	free_tab(env);
	new_env[i] = ft_strdup(new_var);
	new_env[i++] = NULL;
	return (new_env);
}

/* Permet de gérer l'export des variables d'environnement. */
void	handle_export_var(t_data *data)
{
	int		i;
	char	*var_name;

	i = 0;
	if (data->cmd->args[2])
		msg_error("export: too many arguments.\n");
	if (!data->cmd->args[1])
	{
		export_sorted_var(data->env);
		print_export(data->env);
	}
	if (ft_strchr(data->cmd->args[1], '='))
	{
		var_name = ft_strnstr(data->cmd->args[i], data->cmd->args[0],
			ft_strlen(data->cmd->args[0]));
		replace_var(var_name, get_env_len(data->env), data->env);
		export_sorted_var(data->env);
		print_export(data->env);
	}
	else
	{
		var_name = ft_strnstr(data->cmd->args[i], data->cmd->args[0],
			ft_strlen(data->cmd->args[0]));
		add_var_env(data->env, var_name);
		export_sorted_var(data->env);
		print_export(data->env);
	}
}
