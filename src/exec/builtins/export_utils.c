/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:24:50 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/05/14 12:39:12 by mgodefro         ###   ########.fr       */
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
//	printf("ENTRY IN PRINT_EXPORT\n");

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

/* Free un tableau deux dimensions. */
void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

char	*get_var_name(char *arg)
{
//	printf("ENTRY IN GET_VAR_NAME\n");

	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (ft_substr(arg, 0, i));
}
