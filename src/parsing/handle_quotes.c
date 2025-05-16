/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:10:41 by aeudes            #+#    #+#             */
/*   Updated: 2025/05/16 17:56:22 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_quote	get_quote_type(char *input)
{
	int		i;
	t_quote	quote;

	i = 0;
	quote = NONE;
	while (input[i])
	{
		if (input[i] == '\'' && quote == NONE)
			return (SINGLE);
		if (input[i] == '"' && quote == NONE)
			return (DOUBLE);
		i++;
	}
	return (NONE);
	
}

int	check_quote_state(char *input)
{
	int i;
	t_quote quote_state;
	
	i = 0;
	quote_state = NONE;
	while (input[i] != '\0') 
	{
		if (input[i] == '\'' && quote_state == NONE)
			quote_state = SINGLE;
		else if (input[i] == '\'' && quote_state == SINGLE)
			quote_state = NONE;
		else if (input[i] == '\"' && quote_state == NONE)
			quote_state = DOUBLE;
		else if (input[i] == '\"' && quote_state == DOUBLE)
			quote_state = NONE;
		i++;
	}
	if (quote_state != NONE)
	{
		ft_putstr_fd(ERR_QUOTE, STDERR_FILENO);
		return(ERROR);
	}
	return (SUCCESS);
}






