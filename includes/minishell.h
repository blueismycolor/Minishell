/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:49:52 by egatien           #+#    #+#             */
/*   Updated: 2025/04/23 16:39:36 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERR_PIPE	"Error: failed to create pipe"
# define ERR_MALLOC	"Error: memory allocation failed (malloc)"
# define ERR_QUOTE	"Error: unmatched or invalid quote"
# define ERR_CMD	"Error: command execution failed"
# define ERR_EXECVE	"Error: execve system call failed"
# define SUCCESS	0
# define ERROR		1

# include "./libft-complete/libft/libft.h"
# include "./libft-complete/ft_printf/ft_printf.h"

//tokens
typedef enum e_type
{
	INPUT = 1,	// "<"  : redirection de l'entrée
	HEREDOC,	// "<<" : redirection here-doc
	TRUNC,		// ">"  : redirection de la sortie (écrasement)
	APPEND,		// ">>" : redirection de la sortie (ajout à la fin)
	PIPE,		// "|"  : pipe
	CMD			// commande principale et argument(ex: ls -al, cat)
}	e_type;

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
