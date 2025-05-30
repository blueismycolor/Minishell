/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:34:20 by mgodefro          #+#    #+#             */
/*   Updated: 2025/05/30 13:39:49 by egatien          ###   ########.fr       */
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

void	update_pwd(t_data *data)
{
	char	*tmp;
	char	buffer[4096];

//	printf("Before update: pwd=%p | \"%s\"\nold_pwd=%p | \"%s\"\n\n", data->pwd, data->old_pwd, data->pwd, data->old_pwd);
	if (data->pwd)
		tmp = ft_strdup(data->pwd);
	else
		tmp = NULL;
	if (data->old_pwd)
	{
//		printf("Freeing old_pwd at %p | \"%s\"\n\n", data->old_pwd, data->old_pwd);
		free(data->old_pwd);
		data->old_pwd = NULL;
	}
	data->old_pwd = tmp;
	if (getcwd(buffer, sizeof(buffer)) != NULL)
	{
		if (data->pwd)
		{
//			printf("Freeing pwd at %p | \"%s\"\n\n", data->pwd, data->pwd);
			free(data->pwd);
			data->pwd = NULL;
		}
		data->pwd = ft_strdup(buffer);
	}
	else
		perror("getcwd");
//	printf("After update: pwd=%p | \"%s\"\nold_pwd=%p | \"%s\"\n", data->pwd, data->old_pwd, data->pwd, data->old_pwd);
	}

void	handle_cd(t_data *data)
{
//	printf("ENTRY HANDLE_CD\n");
	char	*target;
	int		redir_value;

	data->return_value = 0;
	target = NULL;
	if (data->cmd->nb_params > 1)
		error(data, "cd: too many arguments.\n", 1);
	if (!data->cmd->args[1] || ft_strcmp(data->cmd->args[1], "~") == 0)
		target = getenv("HOME");
	else if (ft_strcmp(data->cmd->args[1], "-") == 0)
	{
		if (!data->old_pwd)
			error(data, "cd: OLDPWD not set.\n", 1);
		target = data->old_pwd;
		printf("%s\n", target);
	}
	else
		target = data->cmd->args[1];
	if (!target)
		error(data, "cd: HOME not set.\n", 1);
	redir_value = chdir(target);
	if (redir_value != 0)
		error(data, "cd: no such file or directory.\n", 1);
	update_pwd(data);
}

