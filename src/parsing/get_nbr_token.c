/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nbr_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:32:44 by egatien           #+#    #+#             */
/*   Updated: 2025/06/25 13:45:36 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_quotes(char *out, int i) // fonction qui check les quotes
{
	while (out[i] != '|' && out[i] != '>' && out[i] != '<' && out[i] != '\0')
	{
		if (out[i] == '\'')
		{
			i++;
			while (out[i] != '\'' && out[i] != '\0')
				i++;
			if (out[i] == '\0')
				return (-1);
		}
		if (out[i] == '"')
		{
			i++;
			while (out[i] != '"' && out[i] != '\0')
				i++;
			if (out[i] == '\0')
				return (-1);
		}
		i++;
	}
	return (i);
}

/* 

	fonction dont le but est de compter le nombre de token
	dans une chaine et check egalement si nombres impair de quotes

*/
int	get_nbr_tokens(char *out)
{
	int		i;
	int		count;

	count = 1;
	i = 0;
	while (out[i] != '\0')
	{
		while (ft_isspace(out[i]) && out[i] != '\0')
			i++;
		if (out[i] != '|' && out[i] != '>'
			&& out[i] != '<' && !ft_isspace(out[i]) && out[i] != '\0')
			count ++;
		i = check_for_quotes(out, i);
		if (i == -1)
			return (i);
		if ((out[i] == '|' || out[i] == '>' || out[i] == '<'))
		{
			count++;
			i++;
			if ((out[i] == '>' || out[i] == '<')
				&& (out[i - 1] == '>' || out[i - 1] == '<'))
				i++;
		}
	}
	return (count - 1);
}
