/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximegdfr <maximegdfr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:24:50 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/06/01 16:21:32 by maximegdfr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Permet d'obtenir la taille de **env. */
int	get_env_len(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
		i++;
	return (i);
}

/* Print les variables d'environnement correctement. */
void	print_export(char **env)
{
	int		i;
	char	*equal;

	i = 0;
	while (env[i])
	{
		equal = ft_strchr(env[i], '=');
		if (equal)
			printf("export %.*s=\"%s\"\n", (int)(equal - env[i]),
				env[i], equal + 1);
		else
			printf("export %s\n", env[i]);
		i++;
	}
}

char	*get_var_name(char *arg)
{
	int		i;
	char	*name;

	i = 0;
	name = NULL;
	while (arg[i] && arg[i] != '=')
		i++;
	name = ft_substr(arg, 0, i);
	if (is_valid_var_name(name))
		return (name);
	else
		return (NULL);
}

bool	is_valid_var_name(char *arg)
{
	int	i;

	i = 1;
	if (!arg || !arg[0])
		return (false);
	if (!(isalpha(arg[0]) || arg[0] == '_'))
		return (false);
	while (arg[i])
	{
		if (!(isalnum(arg[i]) || arg[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}
