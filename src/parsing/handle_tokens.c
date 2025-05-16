/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:18:03 by aeudes            #+#    #+#             */
/*   Updated: 2025/05/16 17:57:43 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_type get_token_type(char *input)
{
	if (ft_strncmp(input, ">>", 2) == 0)
		return (APPEND);
	else if (ft_strncmp(input, "<<", 2) == 0)
		return (HEREDOC);
	else if (ft_strncmp(input, ">", 1) == 0)
		return (TRUNC);
	else if (ft_strncmp(input, "<", 1) == 0)
		return (INPUT);
	else if (ft_strncmp(input, "|", 1) == 0)
		return (PIPE);
	else
		return (CMD);
}

t_token 	*create_token(t_token **head, char *str, t_type type, t_quote quote)
{
	t_token	*new_token;
	t_token	*tmp;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->str = ft_strdup(str);
	if (!new_token->str)
		return(free(new_token), NULL); // free new token ? 
	new_token->type = type;
	new_token->quote = quote;
	new_token->has_expansion = false;
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