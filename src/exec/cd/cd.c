/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximegdfr <maximegdfr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:34:20 by mgodefro          #+#    #+#             */
/*   Updated: 2025/04/26 17:36:39 by maximegdfr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Change le repertoire de travail actuel via un chemin relatif ou absolu.
** Si pas d'operande ET HOME non defini : comportement a definir.
** Si pas d'operande ET HOME defini : HOME devient l'operande.
** Si operande ./.. : verification du chemin -> valide = maj repertoire || invalide = msg erreur.
** Si operande .. : maj vers "PATH= un repertoire en moins".
** Si operande - : maj vers OLDPWD
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

void	update_pwd(t_data *data, char *buffer)
{
	if (data->old_pwd)
		free(data->old_pwd);
	if (data->pwd)
		data->old_pwd = ft_strdup(data->pwd);
	else
		data->old_pwd = NULL;
	if (getcwd(buffer, sizeof(buffer)))
	{
		if (data->pwd)
			free(data->pwd);
		data->pwd = ft_strdup(buffer);
	}
}

void	handle_cd(t_data *data, char **args, char **env)
{
	char	*target;
	char	*pwd; // Dans data ?
	char	*home; // Dans data ?
	char	*old_pwd; // Dans data ?
	char	buffer[4096];
	int		redir_value;

	target = NULL;
	pwd = getenv("PWD");
	home = geten("HOME");
	old_pwd = getenv("OLDPWD");
	if (args[2])
		msg_error("cd: too many arguments.\n");
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		target = home;
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (!old_pwd)
			msg_error("cd: OLDPWD not set.\n");
		target = old_pwd;
		printf("%s\n", target);
	}
	else
		target = args[1];
	if (!target)
		msg_error("cd: HOME not set.\n");
	redir_value = chdir(target);
	if (redir_value != 0)
		msg_error("cd: no such file or directory.\n");
	update_pwd(data, buffer);
}
