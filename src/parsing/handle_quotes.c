/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:10:41 by aeudes            #+#    #+#             */
/*   Updated: 2025/04/29 15:33:08 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* simple quotes ? ou double quotes ?* sinon il n'y a pas de quote*/
t_quote	get_quote_type(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (SINGLE);
		if (str[i] == '\"')
			return (DOUBLE);
		i++;
	}
	return (NONE);
}

/*
Si les simples quotes ne sont pas encore ouverts (quote_state == NONE),
des qu'on tombe dessus, ça met quote_state à SINGLE.
Si les simples quotes sont ouverts (quote_state == SINGLE) des qu'on tombe dessus,
ca met quote_state a NONE donc ca ferme les quotes.

Si les doubles quotes ne sont pas encore ouverts (quote_state == NONE),
des qu'on tombe dessus, ça met quote_state à DOUBLE.
Si les doubles quotes sont ouverts (quote_state == DOUBLE) des qu'on tombe dessus,
ca met quote_state a NONE donc ca ferme les quotes.
*/
t_quote get_quote_state(char *str)
{
	int i;
	t_quote quote_state;
	
	i = 0;
	quote_state = NONE;
	
	while (str[i] != '\0') 
	{
		if (str[i] == '\'' && quote_state == NONE)
			quote_state = SINGLE;
		else if (str[i] == '\'' && quote_state == SINGLE)
			quote_state = NONE;
		else if (str[i] == '\"' && quote_state == NONE)
			quote_state = DOUBLE;
		else if (str[i] == '\"' && quote_state == DOUBLE)
			quote_state = NONE;
	}
	i++;
	return (quote_state);
}






