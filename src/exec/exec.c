/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:06:01 by tlair             #+#    #+#             */
/*   Updated: 2025/07/02 16:56:24 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		return (ft_strdup(cmd));
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
	free_tcmd(cmd);
	free_data(data);
	exit(127);
}

static void	proc_init(t_data *data)
{
	close(data->saved_stdin);
	close(data->saved_stdout);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	process(t_data *data, t_cmd *cmd)
{
	char		*cmd_path;
	int			temp_return_value;

	proc_init(data);
	if (!cmd->args || !cmd->args[0])
	{
		free_for_exit(data);
		exit(0);
	}
	cmd_path = find_command_path(data, cmd->args[0]);
	if (!cmd_path)
		handle_no_path(data, cmd);
	execve(cmd_path, cmd->args, data->env);
	free(cmd_path);
	temp_return_value = data->return_value;
	free_tcmd(data->cmd);
	free_data(data);
	temp_return_value = 1;
	if (errno == EACCES || errno == EPERM || errno == EROFS
		|| errno == ENOTDIR)
		temp_return_value = 126;
	else if (errno == ENOENT)
		temp_return_value = 127;
	perror("\033[1;31mError\033[0m");
	exit(temp_return_value);
}
