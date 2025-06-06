/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:49:52 by egatien           #+#    #+#             */
/*   Updated: 2025/06/06 18:14:33 by tlair            ###   ########.fr       */
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

# define MAX_CMDS INT_MAX
# define SIZE_MAX 20
# define SPACE ' '

/*********************/
/* Messages d'erreur */
/*********************/
# define ERR_PIPE			"failed to create pipe."
# define ERR_REDIR			"invalid redirection."
# define ERR_MALLOC			"memory allocation failed,"
# define ERR_QUOTE			"unmatched or invalid quote."
# define OPEN_SNG_QUOTE		"unclosed single quote."
# define OPEN_DBL_QUOTE		"unclosed double quote."
# define ERR_CMD			"command execution failed."
# define ERR_QUOTE_OPEN		"unclosed quote."
# define ERR_EXECVE			"execve system call failed."
# define ERR_FORK			"fork failed."
# define ERR_DUP			"dup failed."
# define NO_PATH			"no such file or directory."
# define ERR_EOF			"unexpected EOF."
# define TOO_LONG			"argument list too long."
# define ERR_VA_ENV			"unboud variable."			// Erreur avec variable non initialisee (set -u)
# define ERR_SYN			"syntax error in expression."	// Manque un i++ ou qqch dans le genre
# define ERR_FD				"bad file descriptor."		// Fermeture accidentelle dun fd
# define ERR_HEREDOC		"warning: here-document delimited by end-of-file."
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
	char			*del;
	t_type			type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			*cmd;		// commande principale
	bool			is_builtin;	// true si builtin
	char			**args;		// arguments & options de la commande
	int				nb_params;	// nombre d'arguments
	bool			has_redir;	// true si redirection
	t_redir			*redir;		// redirection (fichier, type)
	int				fd;			// fichier
	t_quote			quote;		// type de quote
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_data
{
	t_cmd			*cmd;			// commande, arguments, redirections, etc.
	char			**env;			// variables d'environnement
	char			*pwd;
	char			*old_pwd;
	int				return_value;	// valeur de retour de la derniere commande
	char			**history;
	int				saved_stdin;
	int				saved_stdout;
	bool			is_exit;		// true si on doit quitter le shell (temporaire ou pas)
}	t_data;

/********************/
/* Variable globale */
/********************/
extern int	g_signal;		// 127 = command not found || 126 = permission failed || 1 = general error

/*********************/
/* Fonctions parsing */
/*********************/

//create_list_tcmd0.c
t_cmd	*tcmd_init(char *input, t_data *data);
t_cmd	*init_cmd_node(t_cmd **cmd_list, t_cmd **current);
char	**realloc_args(char **args, int size);
void	add_arg(t_cmd *cmd, char *str);
void	add_redir(t_cmd *cmd, char *del, t_type type);

//create_list_tcmd1.c
char	**remove_filename(char **args);
void	fill_cmd_from_tokens(t_cmd *cmd, t_token **token);
t_cmd	*fill_special_cmd(t_token **tokens, t_cmd **head, t_cmd **last, t_cmd **new_cmd);
t_cmd	*create_list_tcmd(t_token *token);
t_cmd	*give_isbuiltin(t_cmd	*result);

//expansion0.c
char	*ft_tabstrnstr(const char *str, const char *to_find);
int		last_exit_status(int exit_status);
char	*search_env(char *env_name, char **envp);
char	*get_env_value(char *str, int index, char **envp);
int		ft_isspecial(char c);

//expansion1.c
int		parsing_env_var(char *str, char *result, int tmp);
char	*get_special_env_value(char *str, int index, char **envp);
char	*get_env_name(char *str, int index, char **envp);
int		get_end_of_second_part(char *str, int index);
char	*put_third_part(int i, char *str);

//expansion2.c
char	*get_result(char * name_of_env, char * first_part, char *second_part);
char	*place_env_in_str(char *str, int index, char *name_of_env);
char	*put_env(char *str, char **envp);
char	*set_env(char *str, char **envp);

//free_struct.c
void	free_list(t_token *head);
void	free_tab(char **tab);
void	free_redir(t_redir *redirection);
void	free_tcmd(t_cmd *list);

//ft_remove_quote.c
bool	check_quotes_state(char c, bool singlequote);
int		pass_single_quotes(char *str, int i);
char	*ft_remove_quotes(char *str);
t_quote	quotes_state_to_remove(char c, t_quote in_quotes);

//get_args.c
int		count_args(char *str);
char	*get_word(int i, int end, char *str);
char	**ft_getargs(char *str, char **result);
char	**set_args(char *str);

//get_nbr_token.c
int		check_for_quotes(char *out, int i);
int		get_nbr_tokens(char *out);

//get_token_tabstr.c
int		check_redirections(char *str, int end);
char	**setup_variables(bool *command, int *j, int *i, char *str);
int		get_second_tokens(char *str, char **result, int *j, int end);
char	**put_token_in_tabstr(char *str);
t_token	*get_token(char *str);

//get_token_utils0.c
int		pass_quotes(int i, char *str);
int		get_end_of_token(int i, char *str, bool *command);
char	*get_str_token(char *str, int i, int end);
char	*put_second_tokens(char *str, int end);


//get_token_utils1.c
t_token	*create_token(t_token **head, char *str, t_type type, t_quote quote);
t_type	get_token_type(char *str);
t_quote	get_quote_type(char *str);
bool	check_for_expansion(char *str);


//main.c
void	print_tab(char	**tab);


//parsing0.c
int		process_input(char *input);
bool	validate_input(char *input);
bool	check_pipe_syntax(char *input, int i);
int		check_quote_syntax(char *input, int i);
bool	check_redirection_syntax(char *input, int i, int j);

//parsing1.c
bool	is_in_quotes(char *input, int i);
bool	is_in_double_quotes(char *input, int i);
int		is_space(char c);
int		skip_space(char *input, int i);
void	print_tokens(t_cmd *input);


/***********************/
/* Fonctions executing */
/***********************/

void	sigint_handler(int sig);
void	execute_command(t_data *data, t_cmd *cmd);
void	process(t_data *data, t_cmd *cmd, char	**environ);
void	exit_process(t_data *data, pid_t pid, int status);
void	exit_with_code(t_data *data, int exit_code);

void	error(t_data *data, char *msg, int error_code);
void	msg_error(char *msg);
char	*find_command_path(const char *cmd);
char	**create_arguments(t_cmd *token);

/* cd.c */
void	update_pwd(t_data *data);
void	handle_cd(t_data *data);

/* cd_utils.c */
void	replace_var_in_cd(t_data *data, char *new_var, int var_index);
char	**copy_env_cd(t_data *data, char **new_env, char *new_var, int i);
int		var_index_cd(t_data *data, char *var_name);
char	*get_env_value_cd(t_data *data, char *key);

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
char		*get_var_name(char *arg);
bool		is_valid_var_name(char *arg);

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


/* Redirection handling */
bool		handle_redir(t_data *data, t_cmd *cmd);
void		handle_input(t_data *data);
void		handle_trunc(t_data *data);
void		handle_append(t_data *data);
void		reset_fd(t_data *data);

/* heredoc.c */
int			preprocess_heredocs(t_cmd *cmds);
int			read_heredoc_content(int fd, char *del);
char		*generate_heredoc_filename(void);
int			is_delimiter(char *line, char *del);

/* Minishell_process */
void		handle_pipes(t_data *data);
void		select_builtin(t_data *data);

/*******************/
/* Utils & history */
/*******************/
void		free_tokens(t_data *data);
void		ft_free_array(char **array);
void		print_data(t_data *data);

void		add_to_history(t_data *data, const char *input);
void		init_history(t_data *data);
void		free_history(t_data *data);

#endif
