/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_of_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:01:32 by egatien           #+#    #+#             */
/*   Updated: 2025/05/07 15:25:41 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_end_of_second_part(char *str, int index)
{
	if (ft_isdigit(str[index + 1]))
		return (index + 2);
	if (str[index + 1] == '?')
		return (index + 2);
	if (str[index + 1] == '{')
	{
		while (str[index] != '}')
			index++;
		return (index + 1);
	}
	index++;
	while (ft_isalpha(str[index]) || str[index] == '_'
		|| ft_isdigit(str[index]))
	{
		index++;
	}
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
	while (result[i] != '\0')
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
		i++;
	}
	return (result);
}

// int	main(int argc, char **argv, char **env)
// {
// 	char	*result = "$USER fdvdfv $PATH #jghg$HOME\0";

// 	if (argc && argv)
// 		result = set_env(argv[1], env);
// 	printf("result : |%s|\n", result);
// 	free(result);
// }
