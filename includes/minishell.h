/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:49:52 by egatien           #+#    #+#             */
/*   Updated: 2025/04/23 14:58:40 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// message d'erreur



// tokens
typedef enum e_type
{
	INPUT = 1,	// "<"  : redirection de l'entrée
	HEREDOC,	// "<<" : redirection here-doc
	TRUNC,		// ">"  : redirection de la sortie (écrasement)
	APPEND,		// ">>" : redirection de la sortie (ajout à la fin)
	PIPE,		// "|"  : pipe
	CMD			// commande principale et argument(ex: ls -al, cat)
};

typedef struct t_command
{
	char	*str;
	char	**command;
	e_type	type;

}	t_command;

// variable global

int	signal;

//fonctions parsing

//fonctions exec

#endif