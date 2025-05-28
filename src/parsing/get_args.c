/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:41:50 by tlair             #+#    #+#             */
/*   Updated: 2025/05/28 14:41:55 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// int	count_for_quotes(int i, char *str, int *count)
// {

// 	return (i);
// }

int	count_args(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			count++;
			while (str[i] == ' ')
				i++;
		}
		i = pass_quotes(i, str);
		if (str[i] == '\0')
			break;
		i++;
	}
	count++;
	return (count);
}

char	*get_word(int i, int end, char *str)
{
	int		index;
	char	*result;

	index = 0;
	result = malloc(sizeof(char) * (end - i) + 1);
	while (i < end)
	{
		result[index] = str[i];
		index++;
		i++;
	}
	result[index] = '\0';
	return (result);
}

char	**ft_getargs(char *str, char **result)
{
	int	i;
	int	j;
	int	end;

	end = 0;
	i = 0;
	j = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] != '\0')
	{
		while (str[end] == ' ')
			end++;
		i = end;
		while (str[end] != ' ' && str[end] != '\0')
		{
			end = pass_quotes(end, str);
			end++;
		}
		result[j] = get_word(i, end, str);
		j++;
		i = end;
	}
	result[j] = NULL;
	return (result);
}

char	**set_args(char *str)
{
	char	**result;
	int		count;
	int		i;

	i = 0;
	count = count_args(str);
	result = malloc(sizeof(char *) * (count + 1));
	result = ft_getargs(str, result);
	while (result[i])
	{
		result[i] = ft_remove_quotes(result[i]);
		i++;
	}
	return (result);
}
// en gros il va falloir tout decouper. Les quotes en gros se suppriment faut les enlever.


/*

EN GROS : 

	TANT QU'IL N'Y A PAS D'ESPACES LE QUOTE EST TOUJOURS VALIDE.
	LISTE D'EXEMPLE : 
	- ls -al = 2 token : "ls", "-al"
	- ls' -al' = 1 token : "ls -al"

	EN GROS TU CREER UN SPLIT QUI VA RECUPERER TOUT AVEC LES QUOTES
	-> ENSUITE ON RETIRE LES QUOTES. COMMENT ?? FACILE !!! 
		-> STRJOIN DES DEUX CHAINES AVANT ET APRES LE PREMIER QUOTE. ET POUR LE DEUXIEME ??
			-> ON FAIT PAREIL.

*/

