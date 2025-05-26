/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:10:41 by aeudes            #+#    #+#             */
/*   Updated: 2025/05/26 18:01:33 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
int	check_quote_state(char *input)
{
	t_quote	quote_state;
	int		i;
	
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

*/




