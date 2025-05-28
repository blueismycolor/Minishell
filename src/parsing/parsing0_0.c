/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing0_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:56:31 by aeudes            #+#    #+#             */
/*   Updated: 2025/05/28 14:42:29 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*ft_parse(char *str)/* le but de cette fonction est de renvoyer une liste chaine de token (c'est la fonction principale en gros)*/
{
	(void)str;
	return (NULL); //temp
}

bool		is_in_quotes(char *input, int i)
{
	int index;
	int	quote_count;
	
	index = 0;
	quote_count = 0;
	while (index < i)
	{
		if (input[index] == '\'')
			quote_count++;
		index++;
	}
	if (quote_count % 2 != 0)
		return (true);
	return (false);
}

bool		is_in_double_quotes(char *input, int i)
{
	int	index;
	int	quote_count;

	index = 0;
	quote_count = 0;
	while (index < i)
	{
		if (input[index] == '"')
			quote_count++;
		index++;
	}
	if (quote_count % 2 != 0)
		return (true);
	return (false);
}
























