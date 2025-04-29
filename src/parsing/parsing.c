/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:28:11 by egatien           #+#    #+#             */
/*   Updated: 2025/04/29 15:34:41 by tlair            ###   ########.fr       */
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


t_command	*ft_parse(char *str) 	/* le but de cette fonction est de renvoyer une liste chaine de token (c'est la fonction principale en gros)*/
{
	(void)str;
	return (NULL); //temp
}