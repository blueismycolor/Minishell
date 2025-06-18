/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:06:01 by tlair             #+#    #+#             */
/*   Updated: 2025/06/18 12:53:50 by tlair            ###   ########.fr       */
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

static char *ft_getenv(char **env, const char *name) {
    size_t len = ft_strlen(name);
    for (int i = 0; env[i] != NULL; i++) {
        if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=') {
            return env[i] + len + 1; // Pointeur sur la valeur après '='
        }
    }
    return NULL;
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
	{
		error(data, ERR_CMD_NOT_FOUND, 127);
		ft_putendl_fd(cmd->args[0], 2);
		ft_free_array(cmd->args);
		exit(127);
	}
	execve(cmd_path, cmd->args, data->env);
	free(cmd_path);
	if (errno == EACCES)
		data->return_value = 126;
	else if (errno == ENOENT)
		data->return_value = 127;
	else
		data->return_value = 1;
	perror("\033[1;31mError\033[0m");
	ft_free_array(cmd->args);
	exit(data->return_value);
}

void	exit_proc_sig_init(pid_t pid, int *status)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, status, 0);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	exit_process(t_data *data, pid_t pid, int status)
{
	int	sig;

	sig = 0;
	exit_proc_sig_init(pid, &status);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			write(1, "\n", 1);
			data->return_value = 130;
		}
		else if (sig == SIGQUIT)
		{
			if (WCOREDUMP(status))
			write(1, "Quit (core dumped)\n", 19);
			else
			write(1, "Quit\n", 5);
			data->return_value = 131;
		}
	}
	else if (WIFEXITED(status))
		data->return_value = WEXITSTATUS(status);
}
