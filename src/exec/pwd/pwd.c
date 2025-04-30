/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximegdfr <maximegdfr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:11:12 by mgodefro          #+#    #+#             */
/*   Updated: 2025/04/26 17:33:03 by maximegdfr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	handle_pwd(char **env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		msg_error("pwd: error: getcwd can't access parent directories.\n");
	printf("%s\n", pwd);
	free(pwd);
}
