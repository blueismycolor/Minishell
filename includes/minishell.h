/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:49:52 by egatien           #+#    #+#             */
/*   Updated: 2025/04/23 16:50:54 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft-complete/libft/libft.h"
# include "./libft-complete/ft_printf/ft_printf.h"

//error messages
# define ERR_PIPE	"Error: failed to create pipe"
# define ERR_MALLOC	"Error: memory allocation failed (malloc)"
# define ERR_QUOTE	"Error: unmatched or invalid quote"
# define ERR_CMD	"Error: command execution failed"
# define ERR_EXECVE	"Error: execve system call failed"
# define SUCCESS	0
# define ERROR		1

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

// variable globale
int	signalvar;

//fonctions parsing

//fonctions exec

#endif
