/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:30:11 by egatien           #+#    #+#             */
/*   Updated: 2025/06/30 15:16:10 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_quote	quotes_state_to_remove(char c, t_quote in_quotes)
{
	if (c == '"')
	{
		if (in_quotes == NONE)
			in_quotes = DOUBLE;
		else if (in_quotes == DOUBLE)
			in_quotes = NONE;
	}
	if (c == '\'')
	{
		if (in_quotes == NONE)
			in_quotes = SINGLE;
		else if (in_quotes == SINGLE)
			in_quotes = NONE;
	}
	return (in_quotes);
}

void	str_without_quotes_init(int *index_str, int *index_result,
	t_quote *in_quotes)
{
	*index_str = 0;
	*index_result = 0;
	*in_quotes = NONE;
}

static char	*str_without_quotes(char *str, int count)
{
	char	*result;
	int		index_str;
	int		index_result;
	t_quote	in_quotes;

	str_without_quotes_init(&index_str, &index_result, &in_quotes);
	result = malloc(sizeof(char) * (count + 1));
	if (!result)
		return (NULL);
	while (str[index_str] != '\0')
	{
		in_quotes = quotes_state_to_remove(str[index_str], in_quotes);
		if ((str[index_str] == '"' && in_quotes != SINGLE)
			|| (str[index_str] == '\'' && in_quotes != DOUBLE))
		{
			index_str++;
			continue ;
		}
		result[index_result] = str[index_str];
		index_str++;
		index_result++;
	}
	result[index_result] = '\0';
	free(str);
	return (result);
}

char	*ft_remove_quotes(char *str)
{
	t_quote	in_quotes;
	int		count;
	int		i;
	t_quote	prev_state;

	count = 0;
	i = 0;
	in_quotes = NONE;
	while (str[i] != '\0')
	{
		prev_state = in_quotes;
		in_quotes = quotes_state_to_remove(str[i], in_quotes);
		if ((str[i] == '"' && (prev_state == NONE || prev_state == DOUBLE))
			|| (str[i] == '\'' && (prev_state == NONE || prev_state == SINGLE)))
		{
		}
		else
			count++;
		i++;
	}
	return (str_without_quotes(str, count));
}
