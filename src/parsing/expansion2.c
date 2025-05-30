/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:18:57 by aeudes            #+#    #+#             */
/*   Updated: 2025/05/30 14:01:30 by egatien          ###   ########.fr       */
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
	char	*name_of_env;
	int		i;
	char	*result;
	char	*tmp;

	i = 0;
	result = str;
	while (result && result[i] != '\0')
	{
		if (result[i] == '$' && result[i + 1])
		{
			tmp = result;
			name_of_env = get_env_name(result, i, envp);
			result = place_env_in_str(result, i, name_of_env);
			free(tmp);
			result = put_env(result, envp);
			i = 0;
		}
		if (result[i] == '\0')
			break ;
		i++;
	}
	return (result);
}

char	*set_env(char *str, char **envp)
{
	int		i;
	char	*result;
	bool	quotes;

	i = 0;
	quotes = false;
	result = ft_strdup(str);
	while (result[i] != '\0' && result[i] != '$')
	{
		quotes = check_quotes_state(result[i], quotes);
		if (quotes == true)
			i = pass_single_quotes(result, i);
		i++;
	}
	if (result[i] == '\0')
		return (result);
	return (put_env(result, envp));
}
