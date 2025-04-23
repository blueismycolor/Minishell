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


/**************/
/* Librairies */
/**************/
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

/*********************/
/* Messages d'erreur */
/*********************/
# define ERR_PIPE	"Error: failed to create pipe.\n"
# define ERR_MALLOC	"Error: memory allocation failed,\n"
# define ERR_QUOTE	"Error: unmatched or invalid quote.\n"
# define ERR_CMD	"Error: command execution failed.\n"
# define ERR_EXECVE	"Error: execve system call failed.\n"
# define ERR_FORK	"fork failed.\n"
# define ERR_DUP	"dup failed.\n"
# define NO_PATH	"no such file or directory.\n"
# define ERR_EOF	"unexpected EOF.\n"
# define TOO_LONG	"argument list too long.\n"
# define ERR_VA_ENV	"unboud variable.\n"						// Erreur avec variable non initialisee (set -u)
# define ERR_SYN	"syntax error in expression.\n"				// Manque un i++ ou qqch dans le genre
# define ERR_FD		"bad file descriptor.\n"					// Fermeture accidentelle dun fd
# define SUCCESS	0
# define ERROR		1

# include "./libft-complete/libft/libft.h"
# include "./libft-complete/ft_printf/ft_printf.h"

/********************/
/* Structures token */
/********************/
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

/********************/
/* Variable globale */
/********************/
int	signal;			// 127 = command not found || 126 = permission failed || 1 = general error

/*********************/
/* Fonctions parsing */
/*********************/

/***********************/
/* Fonctions executing */
/***********************/
void	msg_error(char *msg);

#endif

