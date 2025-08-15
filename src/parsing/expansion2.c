/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:18:57 by aeudes            #+#    #+#             */
/*   Updated: 2025/06/25 14:21:23 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_result(char *name_of_env, char *first_part, char *second_part)
{
	char	*tmp;
	char	*result;

	if (name_of_env)
	{
		result = ft_strjoin(first_part, name_of_env);
		tmp = result;
		result = ft_strjoin(result, second_part);
		free(tmp);
		free(first_part);
		free(name_of_env);
		free(second_part);
		return (result);
	}
	else
	{
		result = ft_strjoin(first_part, second_part);
		free(first_part);
		free(second_part);
		free(name_of_env);
		return (result);
	}
}

char	*place_env_in_str(char *str, int index, char *name_of_env)
{
	int		i;
	char	*first_part;
	char	*second_part;
	char	*result;

	i = 0;
	first_part = malloc(sizeof(char) * index + 1);
	if (!first_part)
		return (NULL);
	while (i < index)
	{
		first_part[i] = str[i];
		i++;
	}
	first_part[i] = '\0';
	i = get_end_of_second_part(str, index);
	second_part = put_third_part(i, str);
	result = get_result(name_of_env, first_part, second_part);
	return (result);
}

char	*put_env(char *str, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (!ft_isalpha(str[i + 1])
				&& str[i + 1] != '_' && str[i + 1] != '?')
			{
				i++;
				continue ;
			}
			tmp = str;
			str = place_env_in_str(str, i, get_env_name(str, i, envp));
			free(tmp);
			str = put_env(str, envp);
			i = 0;
		}
		if (str[i] == '\0')
			break ;
		i++;
	}
	return (str);
}

char	*set_env(char *str, char **envp)
{
	int		i;
	char	*result;
	t_quote	quotes;

	i = 0;
	quotes = NONE;
	result = ft_strdup(str);
	while (result[i] != '\0' && result[i] != '$')
	{
		quotes = quotes_state_to_remove(result[i], quotes);
		if (quotes == SINGLE)
			i = pass_single_quotes(result, i);
		else
			i++;
	}
	if (result[i] == '\0')
		return (result);
	return (put_env(result, envp));
}
