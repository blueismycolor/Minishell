/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_tabstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:42:08 by tlair             #+#    #+#             */
/*   Updated: 2025/05/28 14:42:13 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redirections(char *str, int end)
{
	int	i;

	if ((str[end] == '>' && str[end + 1] == '>')
		|| (str[end] == '<' && str[end + 1] == '<'))
		i = end + 2;
	else
		i = end + 1;
	return (i);
}

char	**setup_variables(bool *command, int *j, int *i, char *str)
{
	char	**result;

	*command = false;
	*j = 0;
	*i = 0;
	result = malloc(sizeof(char *) * (get_nbr_tokens(str)+ 1));
	if (!result)
		return (NULL);
	return (result);
}

int	get_second_tokens(char *str, char **result, int *j, int end)
{
	if (str[end] != '\0')
	{
		result[*j] = put_second_tokens(str, end);
		(*j)++;
	}
	if (*j >= get_nbr_tokens(str))
	{
		result[*j] = NULL;
		return (0);
	}
	return (1);
}

/*
	fonction principale qui cherche les tokens
	dans la chaine de caracteres et les mets sous forme de tableaux de chaine
*/

char	**put_token_in_tabstr(char *str)
{
	char	**result; // le tableau de chaine qu'on renvoit 
	int		i; // parcourt la chaine de caracteres
	int		j; // parcourt le tableau de chaine
	int		end; //parcourt la chaine jusqu'a la fin d'un token (donc un pipe ou une redirection)
	bool	command;

	result = setup_variables(&command, &j, &i, str); // initialise et malloc les variables
	if (!result)
		return (NULL);
	while (str[i] != '\0')
	{
		while (str[i] == SPACE) //on passe les espaces si il y en a dans la chaine (exemple : "     ls    |  grep")
			i++;
		end = get_end_of_token(i, str, &command); // on cherche la fin du token actuelle dans la chaine. command devient faux si le premier token est un '|' ou '>', '<'
		if (command == true) // donc si command = true c'est qu'il y a une commande en premier token et non un pipe etc
		{
			result[j] = get_str_token(str, i, end); //fonction qui recupere le token de commande et le met dans result[j] notre tableau de chaine
			j++;
		}
		if (!get_second_tokens(str, result, &j, end)) // get_second_tokens va recuperer le token qui est soit un pipe ou une redirection. Si tout les tokens ont ete places on renvoie 0 donc on sort de la boucle
			break ;
		i = check_redirections(str, end); // change la valeur de 'i' par rapport a 'end'.
	}
	return (result);
}
