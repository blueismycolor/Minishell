/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:34:20 by mgodefro          #+#    #+#             */
/*   Updated: 2025/06/19 17:21:56 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_old_pwd(t_data *data)
{
	char	*tmp;
	char	*old_pwd_var;
	int		old_pwd_index;

	old_pwd_index = var_index_cd(data, "OLDPWD");
	if (data->pwd)
	{
		tmp = ft_strdup(data->pwd);
		if (!tmp)
			return ;
	}
	else
		tmp = NULL;
	free(data->old_pwd);
	data->old_pwd = tmp;
	old_pwd_var = ft_strjoin("OLDPWD=", data->old_pwd);
	if (!old_pwd_var)
		return ;
	replace_var_in_cd(data, old_pwd_var, old_pwd_index);
	free(old_pwd_var);
}

void	update_pwd(t_data *data)
{
	char	buffer[4096];
	char	*pwd_var;
	int		pwd_index;

	pwd_index = var_index_cd(data, "PWD");
	if (!getcwd(buffer, sizeof(buffer)))
		return (perror("getcwd"));
	free(data->pwd);
	data->pwd = ft_strdup(buffer);
	if (!data->pwd)
		return ;
	pwd_var = ft_strjoin("PWD=", data->pwd);
	if (!pwd_var)
		return ;
	replace_var_in_cd(data, pwd_var, pwd_index);
	free(pwd_var);
}

void	handle_cd(t_data *data)
{
	char	*target;
	int		result;

	target = NULL;
	if (data->cmd->args[1] && data->cmd->args[2])
		return (error(data, "cd: too many arguments.", 1));
	if (!data->cmd->args[1] || ft_strcmp(data->cmd->args[1], "~") == 0)
		target = get_env_value_cd(data, "HOME");
	else if (ft_strcmp(data->cmd->args[1], "-") == 0)
	{
		if (!data->old_pwd)
			return (error(data, "cd: OLDPWD not set.", 1));
		target = data->old_pwd;
		printf("%s\n", target);
	}
	else
		target = data->cmd->args[1];
	if (!target)
		return (error(data, "cd: HOME not set.", 1));
	result = chdir(target);
	if (result != 0)
		return (error(data, "cd: no such file or directory.", 1));
	update_old_pwd(data);
	update_pwd(data);
}
