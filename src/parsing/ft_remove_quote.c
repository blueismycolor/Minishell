/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:41:39 by tlair             #+#    #+#             */
/*   Updated: 2025/05/28 14:41:45 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_quotes_state(char c, bool singlequote)
{
	static bool	doublequotes;

	if (c == '"')
	{
		if (doublequotes == false)
			doublequotes = true;
		else
			doublequotes = false;
	}
	if (c == '\'' && !doublequotes)
	{
		if (singlequote == false)
			singlequote = true;
		else
			singlequote = false;
	}
	return (singlequote);
}

int	pass_single_quotes(char *str, int i)
{
	if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'')
			i++;
		return (i);
	}
	return (i);
}
static t_quote	quotes_state_to_remove(char c, t_quote in_quotes)
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

static char	*str_without_quotes(char *str, int count)
{
	char	*result;
	int		index_str;
	int		index_result;
	t_quote	in_quotes;

	index_str = 0;
	index_result = 0;
	in_quotes = NONE;
	result = malloc(sizeof(char) * (count + 1));
	while (str[index_str] != '\0')
	{
		in_quotes = quotes_state_to_remove(str[index_str], in_quotes);
		if (str[index_str] == '"' && in_quotes != SINGLE)
			index_str ++;
		if (str[index_str] == '\'' && in_quotes != DOUBLE)
			index_str++;
		if (str[index_str] == '\0')
			break ;
		result[index_result] = str[index_str];
		index_str++;
		index_result ++;
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
		if ((str[i] == '"' && (prev_state == NONE || prev_state == DOUBLE)) ||
			(str[i] == '\'' && (prev_state == NONE || prev_state == SINGLE)))
		{
			// c'est une quote d'ouverture ou fermeture, ne rien faire
		}
		else
			count++;
		i++;
	}
	return (str_without_quotes(str, count));

}
