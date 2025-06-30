/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:06:01 by tlair             #+#    #+#             */
/*   Updated: 2025/06/30 18:27:03 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	char	*result;

	if (!s1 || !s2 || !s3)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, s3);
	free(tmp);
	return (result);
}

static char	*ft_getenv(char **env, const char *name)
{
	size_t	len;
	int		i;

	len = ft_strlen(name);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*find_command_path(t_data *data, const char *cmd)
{
	char	*path;
	char	*dir;
	char	*full_path;
	char	*path_copy;

	if (!cmd || !*cmd || ft_strchr(cmd, '/'))
		return (NULL);
	path = ft_getenv(data->env, "PATH");
	if (!path)
		return (NULL);
	path_copy = ft_strdup(path);
	dir = ft_strtok(path_copy, ":");
	while (dir)
	{
		full_path = ft_strjoin3(dir, "/", cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

static void	handle_no_path(t_data *data, t_cmd *cmd)
{
	error(data, ERR_CMD_NOT_FOUND, 127);
	ft_putendl_fd(cmd->args[0], 2);
	free_tcmd(cmd); // ajoute apres
	ft_free_array(data->env); // dans l'ancien cmd->args
	free(data->pwd);// ajoute apres
	free(data);// ajoute apres
	exit(127);
}

void	process(t_data *data, t_cmd *cmd)
{
	char		*cmd_path;

	close(data->saved_stdin);
	close(data->saved_stdout);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!cmd->args || !cmd->args[0])
		exit(update_return_value(data, 0));
	cmd_path = find_command_path(data, cmd->args[0]);
	if (!cmd_path)
		handle_no_path(data, cmd);
	execve(cmd_path, cmd->args, data->env);
	free(cmd_path);
	if (errno == EACCES || errno == EPERM || errno == EROFS
		|| errno == ENOTDIR)
		data->return_value = 126;
	else if (errno == ENOENT)
		data->return_value = 127;
	else
		data->return_value = 1;
	perror("\033[1;31mError\033[0m");
	ft_free_array(cmd->args);
	exit(data->return_value);
}
