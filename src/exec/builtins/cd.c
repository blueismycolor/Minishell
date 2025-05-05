/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:34:20 by mgodefro          #+#    #+#             */
/*   Updated: 2025/05/05 15:16:00 by tlair            ###   ########.fr       */
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

void	handle_cd(t_data *data)
{
	char	*target;
	char	buffer[4096];
	int		redir_value;

	target = NULL;
	if (data->cmd->args[2])
		msg_error("cd: too many arguments.\n");
	if (!data->cmd->args[1] || ft_strcmp(data->cmd->args[1], "~") == 0)
		target = getenv("HOME");
	else if (ft_strcmp(data->cmd->args[1], "-") == 0)
	{
		if (!data->old_pwd)
			msg_error("cd: OLDPWD not set.\n");
		target = data->old_pwd;
		printf("%s\n", target);
	}
	else
		target = data->cmd->args[1];
	if (!target)
		msg_error("cd: HOME not set.\n");
	redir_value = chdir(target);
	if (redir_value != 0)
		msg_error("cd: no such file or directory.\n");
	update_pwd(data, buffer);
}
