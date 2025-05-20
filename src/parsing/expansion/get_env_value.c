/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:58:39 by egatien           #+#    #+#             */
/*   Updated: 2025/05/20 12:39:58 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*search_env(char *env_name, char **envp)
{
	int		index;
	int		i;
	char	*str;

	i = 0;
	index = 0;
	if (!env_name[0])
	{
		free(env_name);
		return (NULL);
	}
	while (envp[index] && !ft_tabstrnstr(envp[index], env_name))
		index++;
	free(env_name);
	while (envp[index] && envp[index][i] != '=')
		i++;
	i++;
	if (!envp[index])
		return (NULL);
	str = ft_strdup(&envp[index][i]);
	if (!str)
		return (NULL);
	return (str);
}

char	*get_env_value(char *str, int index, char **envp)
{
	char	*result;
	int		tmp;
	int		count;
	int		i;

	i = 0;
	count = 0;
	tmp = index;
	while (ft_isdigit(str[tmp]) || ft_isalpha(str[tmp]) || str[tmp] == '_')
	{
		tmp++;
		count++;
	}
	result = malloc(sizeof(char) * (count + 1));
	if (!result)
		return (NULL);
	tmp = index;
	while (ft_isdigit(str[tmp]) || ft_isalpha(str[tmp]) || str[tmp] == '_')
	{
		result[i] = str[tmp];
		tmp++;
		i++;
	}
	result[i] = '\0';
	return (search_env(result, envp));
}

int	parsing_env_var(char *str, char *result, int tmp)
{
	int	i;

	i = 0;
	while (str[tmp] != '}')
	{
		if (!ft_isdigit(str[tmp]) && !ft_isalpha(str[tmp]) && str[tmp] != '_')
		{
			free(result);
			return (0);
		}
		result[i] = str[tmp];
		i++;
		tmp++;
	}
	result[i] = '\0';
	return (1);
}

char	*get_special_env_value(char *str, int index, char **envp)
{
	int		i;
	int		count;
	int		tmp;
	char	*result;

	i = 0;
	count = 0;
	tmp = index;
	if (ft_isdigit(str[tmp + 1]))
		return (NULL);
	while (str[tmp] != '}' && str[tmp] != '\0')
	{
		tmp++;
		count++;
	}
	if (str[tmp] == '\0')
		return (NULL);
	result = malloc(sizeof(char) * count);
	tmp = index;
	tmp++;
	if (!parsing_env_var(str, result, tmp))
		return (NULL);
	return (search_env(result, envp));
}

char	*get_env_name(char *str, int index, char **envp)
{
	int		nbr;
	char	*result;

	index++;
	nbr = 0;
	if (ft_isdigit(str[index]))
	{
		return (NULL);
	}
	if (str[index] == '?')
	{
		result = ft_itoa(last_exit_status(-1));
		return (result);
	}
	if (str[index] == '{')
	{
		result = get_special_env_value(str, index, envp);
		return (result);
	}
	result = get_env_value(str, index, envp);
	return (result);
}
