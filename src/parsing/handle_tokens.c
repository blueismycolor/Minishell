/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:18:03 by aeudes            #+#    #+#             */
/*   Updated: 2025/04/25 15:44:09 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_type	get_operator_type(char *str, int i)
{
	if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (HEREDOC);
		return (INPUT);
	}
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (APPEND);
		return (TRUNC);
	}
	return (CMD);
}
