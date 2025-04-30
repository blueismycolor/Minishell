/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximegdfr <maximegdfr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:57:05 by mgodefro          #+#    #+#             */
/*   Updated: 2025/04/26 17:32:58 by maximegdfr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Verifier et ajouter la mise à jour du code d'erreur à renvoyer
** lors de l'execution de cette fonction.
*/

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

/* Cherche l'index en comparant le nom de celle recherchée avec celles dans env. */
int	get_index(char *var_name, char **env)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		if ((int)j == len && ft_strncmp(env[i], var_name, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

/* Remplace les paramètres de la variable par les nouveaux. */
void	remove_var(int var_index, char **env)
{
	int	i;

	i = var_index;
	if (env[i])
		free(env[i]);
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
}

void	handle_unset(char **args, char **env)
{
	int		index;

	if (!args[1])
		return ;
	if (args[2])
		msg_error("unset: too many arguments.\n");
	index = get_index(args[1], env);
	if (index != -1)
		remove_var(index, env);
}
