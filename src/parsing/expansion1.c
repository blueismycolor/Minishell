/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:18:19 by aeudes            #+#    #+#             */
/*   Updated: 2025/05/30 14:01:00 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parsing_env_var(char *str, char *result, int tmp)
{
	int	i;

	i = 0;
	while (str[tmp] != '}')
	{
		if (ft_isspecial(str[tmp]))
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
	int		count;
	int		tmp;
	char	*result;

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
	char	*result;

	index++;
	if (ft_isdigit(str[index]))
	{
		return (NULL);
	}
	if (str[index] == '?')
	{
		result = ft_itoa(last_exit_status(-1));
		return (result);
	}
	result = get_env_value(str, index, envp);
	return (result);
}

int	get_end_of_second_part(char *str, int index)
{
	if (ft_isdigit(str[index + 1]))
		return (index + 2);
	if (str[index + 1] == '?')
		return (index + 2);
	index++;
	while (ft_isalpha(str[index])
		|| str[index] == '_' || ft_isdigit(str[index]))
		index++;
	return (index);
}

char	*put_third_part(int i, char *str)
{
	int		count;
	int		tmp;
	char	*result;

	tmp = i;
	count = 0;
	while (str[tmp] != '\0')
	{
		tmp++;
		count++;
	}
	result = malloc(sizeof(char) * (count + 1));
	tmp = i;
	count = 0;
	while (str[tmp] != '\0')
	{
		result[count] = str[tmp];
		count++;
		tmp++;
	}
	result[count] = '\0';
	return (result);
}
