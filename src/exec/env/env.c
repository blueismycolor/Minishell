/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximegdfr <maximegdfr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:44:54 by mgodefro          #+#    #+#             */
/*   Updated: 2025/04/26 17:34:24 by maximegdfr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Verifier et ajouter la mise à jour du code d'erreur à renvoyer
** lors de l'execution de cette fonction.
*/

#include "../includes/minishell.h"

typedef enum e_type
{
	INPUT = 1,
	HEREDOC,
	TRUNC,
	APPEND,
	PIPE,
	CMD
}	e_type;

typedef struct s_redir
{
	char	*filename;
	e_type	type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			*cmd;
	bool			is_builtin;
	char			**args;
	int				nb_params;
	bool			has_redir;
	struct s_redir	*redir;
}	t_cmd;

typedef struct s_data
{
	struct s_cmd	*cmd;
	char			**env;
	char			*pwd;
	char			*old_pwd;
	int				return_value;
}	t_data;

void	handle_env(char **args, char **env)
{
	int	i;

	if (args[1])
		msg_error("env: too many arguments.\n");
	else
	{
		i = 0;
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
}
