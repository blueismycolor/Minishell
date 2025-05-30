/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:24:50 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/05/30 14:29:48 by tlair            ###   ########.fr       */
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
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (ft_substr(arg, 0, i));
}
