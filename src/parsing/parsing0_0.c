/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing0_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:50:38 by aeudes            #+#    #+#             */
/*   Updated: 2025/05/16 17:51:36 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
le parsing va se proceder ainsi :
	- compter le nombre de token
	- mettre tous les token dans un tableau de str
	- chaque element du tableau le mettre dans t_command.str
	- definir le type de chaque token present dans t_command.str
	- rediviser t_command.str pour recuperer commande et argument et le mettre dans t_command.command

/!\ gerer les quotes :
	- les quotes si elles s'echainent il faut les concatener pour creer un seul token -> ex : "ls"" -al" == "ls -al"
	- donc dans le cas des quotes, t_command.command a donc une seule chaine dans le tableau. 
*/

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