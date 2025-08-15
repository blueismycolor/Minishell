/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:57:55 by aeudes            #+#    #+#             */
/*   Updated: 2025/05/30 11:08:18 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(t_token **head, char *str, t_type type, t_quote quote)
{
	t_token	*new_token;
	t_token	*tmp;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->str = ft_strdup(str);
	if (!new_token->str)
		return (NULL);
	new_token->type = type;
	new_token->quote = quote;
	new_token->next = NULL;
	if (!*head)
		*head = new_token;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
	return (new_token);
}

t_type	get_token_type(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0 && get_quote_type(str) == NONE)
		return (APPEND);
	else if (ft_strncmp(str, "<<", 2) == 0 && get_quote_type(str) == NONE)
		return (HEREDOC);
	else if (ft_strncmp(str, ">", 1) == 0 && get_quote_type(str) == NONE)
		return (TRUNC);
	else if (ft_strncmp(str, "<", 1) == 0 && get_quote_type(str) == NONE)
		return (INPUT);
	else if (ft_strncmp(str, "|", 1) == 0 && get_quote_type(str) == NONE)
		return (PIPE);
	else
		return (CMD);
}

t_quote	get_quote_type(char *str)
{
	int		i;
	t_quote	quote;

	i = 0;
	quote = NONE;
	while (str[i])
	{
		if (str[i] == '\'' && quote == NONE)
			return (SINGLE);
		if (str[i] == '"' && quote == NONE)
			return (DOUBLE);
		i++;
	}
	return (NONE);
}

bool	check_for_expansion(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}
