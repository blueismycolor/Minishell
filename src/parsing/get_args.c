/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:24:27 by aeudes            #+#    #+#             */
/*   Updated: 2025/06/25 14:20:52 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_args(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (!ft_isspace(str[i]) && str[i] != '\0')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]))
		{
			count++;
			while (ft_isspace(str[i]))
				i++;
		}
		i = pass_quotes(i, str);
		if (str[i] == '\0')
			break ;
		i++;
	}
	count++;
	return (count);
}

char	*get_word(int i, int end, char *str)
{
	int		index;
	char	*result;

	index = 0;
	result = malloc(sizeof(char) * (end - i) + 1);
	while (i < end)
	{
		result[index] = str[i];
		index++;
		i++;
	}
	result[index] = '\0';
	return (result);
}

char	**ft_getargs(char *str, char **result)
{
	int	i;
	int	j;
	int	end;

	end = 0;
	i = 0;
	j = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i] != '\0')
	{
		while (ft_isspace(str[end]))
			end++;
		i = end;
		while (!ft_isspace(str[end]) && str[end] != '\0')
		{
			end = pass_quotes(end, str);
			end++;
		}
		result[j] = get_word(i, end, str);
		j++;
		i = end;
	}
	result[j] = NULL;
	return (result);
}

char	**set_args(char *str)
{
	char	**result;
	int		count;
	int		i;

	i = 0;
	count = count_args(str);
	result = malloc(sizeof(char *) * (count + 1));
	result = ft_getargs(str, result);
	while (result[i])
	{
		result[i] = ft_remove_quotes(result[i]);
		i++;
	}
	return (result);
}
