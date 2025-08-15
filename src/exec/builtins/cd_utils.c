/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:36:25 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/08/15 09:14:10 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_var_in_cd(t_data *data, char *new_var, int var_index)
{
	int		i;
	char	**new_env;

	if (!ft_strchr(new_var, '='))
		return ;
	if (var_index >= 0)
	{
		free(data->env[var_index]);
		data->env[var_index] = ft_strdup(new_var);
	}
	else
	{
		i = 0;
		while (data->env[i])
			i++;
		new_env = malloc(sizeof(char *) * (i + 2));
		if (!new_env)
			msg_error(ERR_MALLOC);
		new_env = copy_env_cd(data, new_env, new_var, i);
		free(data->env);
		data->env = new_env;
	}
}

char	**copy_env_cd(t_data *data, char **new_env, char *new_var, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		new_env[j] = data->env[j];
		j++;
	}
	new_env[i] = ft_strdup(new_var);
	new_env[i + 1] = NULL;
	return (new_env);
}

int	var_index_cd(t_data *data, char *var_name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (data->env[i])
	{
		if (strncmp(data->env[i], var_name, len) == 0
			&& data->env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_env_value_cd(t_data *data, char *key)
{
	int		index;
	char	*equal_sign;

	index = var_index_cd(data, key);
	if (index == -1)
		return (NULL);
	equal_sign = ft_strchr(data->env[index], '=');
	if (!equal_sign || !equal_sign[1])
		return (NULL);
	return (equal_sign + 1);
}
