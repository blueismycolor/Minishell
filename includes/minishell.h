/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:49:52 by egatien           #+#    #+#             */
/*   Updated: 2025/04/30 16:39:08 by mgodefro         ###   ########.fr       */
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

# include "../libft-complete/libft/libft.h"
# include "../libft-complete/ft_printf/ft_printf.h"

/*********************/
/* Messages d'erreur */
/*********************/
# define ERR_PIPE			"failed to create pipe.\n"
# define ERR_MALLOC			"memory allocation failed,\n"
# define ERR_QUOTE			"unmatched or invalid quote.\n"
# define ERR_CMD			"command execution failed.\n"
# define ERR_QUOTE_OPEN		"unclosed quote.\n"
# define ERR_EXECVE			"execve system call failed.\n"
# define ERR_FORK			"fork failed.\n"
# define ERR_DUP			"dup failed.\n"
# define NO_PATH			"no such file or directory.\n"
# define ERR_EOF			"unexpected EOF.\n"
# define TOO_LONG			"argument list too long.\n"
# define ERR_VA_ENV			"unboud variable.\n"			// Erreur avec variable non initialisee (set -u)
# define ERR_SYN			"syntax error in expression.\n"	// Manque un i++ ou qqch dans le genre
# define ERR_FD				"bad file descriptor.\n"		// Fermeture accidentelle dun fd
# define SUCCESS			0
# define ERROR				1

/***************/
/* Types token */
/***************/
typedef enum s_type
{
	INPUT = 1,	// "<"  : redirection de l'entrée
	HEREDOC,	// "<<" : redirection here-doc
	TRUNC,		// ">"  : redirection de la sortie (écrasement)
	APPEND,		// ">>" : redirection de la sortie (ajout à la fin)
	PIPE,		// "|"  : pipe
	CMD,		// commande principale et argument(ex: ls -al, cat)
}	t_type;

/****************/
/* Types quotes */
/****************/
typedef enum s_quote
{
	NONE,
	SINGLE,
	DOUBLE
}	t_quote;

 /*******************/
 /* Structure token */
 /******************/
typedef struct s_redir
{
	char			*filename;
	t_type			type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			*cmd;
	bool			is_builtin;
	char			**args;
	int				nb_params;
	bool			has_redir;
	t_redir			*redir;
	t_quote			quote;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	t_type			type;
}	t_cmd;

typedef struct s_data
{
	t_cmd			*cmd;
	char			**env;
	char			*pwd;
	char			*old_pwd;
	int				return_value;
	char			**historic;
}	t_data;

/********************/
/* Variable globale */
/********************/
extern int	g_signal;		// 127 = command not found || 126 = permission failed || 1 = general error
// merci de ne pas remettre "signal" car ce nom est reserve au systeme

/*********************/
/* Fonctions parsing */
/*********************/
/* get_nbr_tokens.c */
int	check_for_quotes(char *out, int i);
int	get_nbr_tokens(char *out);

/* handle_quotes.c */
t_quote	get_quote_type(char *str);
t_quote get_quote_state(char *str);

/* handle_tokens.c */
int	is_whitespace(char c);
int	is_operator(char c);
t_type	get_operator_type(char *str, int i);

/* parsing.c */
t_cmd	*ft_parse(char *str);

/* expansion part */
int	last_exit_status(int exit_status);
char	*put_env(char *str, char **envp);
char	*set_env(char *str, char **envp);
char	*get_env_name(char *str, int index, char **envp);
char	*get_env_name(char *str, int index, char **envp);
char	*ft_tabstrnstr(const char *str, const char *to_find);

/***********************/
/* Fonctions executing */
/***********************/
/* cd.c */
void	update_pwd(t_data *data, char *buffer);
void	handle_cd(t_data *data);

/* echo.c */
int	is_n_option(char *arg);
void	handle_echo(t_data *data);

/* env.c */
void	handle_env(t_data *data);

/* exit.c */
void	handle_exit(t_data *data, char *input);

/* export_utils.c */
int	get_env_len(char **env);
void	print_export(char **env);
void	free_tab(char **tab);

/* export.c */
int		var_index(char *var_name, char **env);
void	replace_var(char *new_var, int var_index, char **env);
void	export_sorted_var(char **env);
char	**add_var_env(char **env, char *new_var);
void	handle_export_var(t_data *data);

/* pwd.c */
void	handle_pwd(t_data *data);

/* unset.c */
int		get_index(char *var_name, char **env);
void	remove_var(int var_index, char **env);
void	handle_unset(t_data *data);

/* init_data.c */
char	**copy_env(t_data *data, char **environ);
t_data	*init_data(char **environ);
t_cmd	*init_cmd(t_cmd *cmd, char *input);
t_redir	*init_redir(t_redir *redir);



void	msg_error(char *msg);
char	*find_command_path(const char *cmd);
char	**create_arguments(t_cmd *token);
int		main(void);

/*******************/
/* Fonctions utils */
/*******************/
void	free_tokens(t_cmd *cmd);
void	ft_free_array(char **array);

#endif
