/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:49:52 by egatien           #+#    #+#             */
/*   Updated: 2025/05/16 18:02:29 by aeudes           ###   ########.fr       */
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
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft-complete/libft/libft.h"
# include "../libft-complete/ft_printf/ft_printf.h"

#ifndef ECHOCTL
# define ECHOCTL 0001000
#endif

/*********************/
/* Messages d'erreur */
/*********************/
# define ERR_PIPE			"Error: failed to create pipe.\n"
# define ERR_REDIR			"Error: invalid redirection.\n"
# define ERR_MALLOC			"Error: memory allocation failed,\n"
# define ERR_QUOTE			"Error: unmatched or invalid quote.\n"
# define OPEN_SNG_QUOTE		"Error: unclosed single quote.\n"
# define OPEN_DBL_QUOTE		"Error: unclosed double quote.\n"
# define ERR_CMD			"Error: command execution failed.\n"
# define ERR_QUOTE_OPEN		"Error: unclosed quote.\n"
# define ERR_EXECVE			"Error: execve system call failed.\n"
# define ERR_FORK			"Error: fork failed.\n"
# define ERR_DUP			"Error: dup failed.\n"
# define NO_PATH			"Error: no such file or directory.\n"
# define ERR_EOF			"Error: unexpected EOF.\n"
# define TOO_LONG			"Error: argument list too long.\n"
# define ERR_VA_ENV			"Error: unboud variable.\n"			// Erreur avec variable non initialisee (set -u)
# define ERR_SYN			"Error: syntax error in expression.\n"	// Manque un i++ ou qqch dans le genre
# define ERR_FD				"Error: bad file descriptor.\n"		// Fermeture accidentelle dun fd
# define SUCCESS			0
# define ERROR				-1
# define FAIL 				1

/*type token*/
typedef enum s_type
{
	INPUT = 1,	// "<"  : redirection de l'entrée
	HEREDOC,	// "<<" : redirection here-doc
	TRUNC,		// ">"  : redirection de la sortie (écrasement)
	APPEND,		// ">>" : redirection de la sortie (ajout à la fin)
	PIPE,		// "|"  : pipe
	CMD,		// commande principale et argument(ex: ls -al, cat)
}	t_type;

/*type quote*/
typedef enum s_quote
{
	NONE,
	SINGLE,
	DOUBLE
}	t_quote;

/*structure token*/
typedef struct s_token
{
	char			*str;
	t_type			type;
	t_quote			quote;
	bool			has_expansion;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	char			*filename;
	t_type			type;
	struct s_redir	*next; // est-ce qu'on en a besoin ?
}	t_redir;

typedef struct s_cmd
{
	char			*cmd;		// commande principale
	bool			is_builtin;	// true si builtin
	char			**args;		// arguments & options de la commande
	int				nb_params;	// nombre d'arguments
	bool			has_redir;	// true si redirection
	t_redir			*redir;		// redirection (fichier, type)
	t_quote			quote;		// type de quote
	struct s_cmd	*next;
	struct s_cmd	*prev;	// est-ce qu'on en a besoin ?
}	t_cmd;

typedef struct s_data
{
	t_cmd			*cmd;			// commande, arguments, redirections, etc.
	char			**env;			// variables d'environnement
	char			*pwd;
	char			*old_pwd;
	int				return_value;	// valeur de retour de la derniere commande
	char			**history;
}	t_data;

/********************/
/* Variable globale */
/********************/
extern volatile sig_atomic_t	g_signal;		// 127 = command not found || 126 = permission failed || 1 = general error

/*********************/
/* Fonctions parsing */
/*********************/
/* get_nbr_tokens.c */
int			check_for_quotes(char *out, int i);
int			get_nbr_tokens(char *out);

/* handle_quotes.c */
t_quote		get_quote_type(char *input);
t_quote 	check_quote_state(char *input);

/* handle_tokens.c */
int			is_whitespace(char c);
int			is_operator(char c);
t_type		get_token_type(char *input);
t_token 	*create_token(t_token **head, char *str, t_type type, t_quote quote);
t_type 		get_token_type(char *input);

/* parsing.c */
t_cmd		*ft_parse(char *str);

/*parsing0_0.c */
bool		is_in_quotes(char *input, int i);
bool		is_in_double_quotes(char *input, int i);

/*parsing0_1.c*/
int			process_input(char *input);
bool		validate_input(char *input);
bool		check_pipe_syntax(char *input, int i);
int			check_quote_syntax(char *input, int i);
bool		check_redirection_syntax(char *input, int i);

/* expansion part */
int			last_exit_status(int exit_status);
char		*put_env(char *str, char **envp);
char		*set_env(char *str, char **envp);
char		*get_env_name(char *str, int index, char **envp);
char		*get_env_name(char *str, int index, char **envp);
char		*ft_tabstrnstr(const char *str, const char *to_find);

/* search token */
char		**put_token_in_tabstr(char *str); //fonction principale qui cherche les tokens et les mets dans un tableau de chaine
char		*get_str_token(char *str, int i, int end);
char		*put_second_tokens(char *str, int end);
int			get_end_of_token(int i, char *str, bool *command);
int			pass_quotes(int i, char *str);

/***********************/
/* Fonctions executing */
/***********************/
/* cd.c */
void		update_pwd(t_data *data);
void		handle_cd(t_data *data);

/* echo.c */
int			is_n_option(char *arg);
void		handle_echo(t_data *data);

/* env.c */
void		handle_env(t_data *data);

/* exit.c */
int			handle_exit(t_data *data, char *input);

/* export_utils.c */
int			get_env_len(t_data *data);
void		print_export(char **env);
void		free_tab(char **tab);
char		*get_var_name(char *arg);

/* export.c */
int			var_index(t_data *data, char *var_name);
void		replace_var(t_data *data, char *new_var, int var_index);
void		export_sorted_var(t_data *data);
char		**add_var_env(t_data *data, char *new_var);
void		handle_export_var(t_data *data);

/* pwd.c */
void		handle_pwd(t_data *data);

/* unset.c */
int			get_index(char *var_name, char **env);
void		remove_var(int var_index, char **env);
void		handle_unset(t_data *data);

/* init_data.c */
char		**copy_env(t_data *data, char **environ);
t_data		*init_data(char **environ);
t_cmd		*init_cmd(t_cmd *cmd, char *input);
t_redir		*init_redir(t_redir *redir);


void		error(t_data *data, char *msg, int error_code);
void		msg_error(char *msg);
char		*find_command_path(const char *cmd);
char		**create_arguments(t_cmd *token);
void		select_builtin(t_data *data);
int			main(void);

/*******************/
/* Utils & history */
/*******************/
void		free_tokens(t_cmd *cmd);
void		ft_free_array(char **array);
void		print_data(t_data *data);

void		add_to_history(t_data *data, const char *input);
void		init_history(t_data *data);
void		free_history(t_data *data);

#endif
