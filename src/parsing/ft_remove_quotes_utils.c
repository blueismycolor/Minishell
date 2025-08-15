/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:41:17 by egatien           #+#    #+#             */
/*   Updated: 2025/06/03 13:41:54 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
