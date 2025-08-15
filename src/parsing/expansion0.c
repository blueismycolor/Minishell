/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:12:17 by egatien           #+#    #+#             */
/*   Updated: 2025/08/15 09:30:46 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_tabstrnstr(const char *str, const char *to_find)
{
	size_t		name_len;
	size_t		to_find_len;
	const char	*equal_ptr;

	if (!str || !to_find)
		return (NULL);
	equal_ptr = ft_strchr(str, '=');
	if (!equal_ptr)
		return (NULL);
	name_len = equal_ptr - str;
	to_find_len = ft_strlen(to_find);
	if (name_len != to_find_len)
		return (NULL);
	if (ft_strncmp(str, to_find, name_len) == 0)
		return ((char *)str);
	return (NULL);
}

int	last_exit_status(int exit_status)
{
	static int	status_to_return;

	if (exit_status != -1)
		status_to_return = exit_status;
	return (status_to_return);
}

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

int	ft_isspecial(char c)
{
	if (!ft_isdigit(c) && !ft_isalpha(c) && c != '_')
		return (1);
	return (0);
}
