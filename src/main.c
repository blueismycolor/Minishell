/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:31:27 by egatien           #+#    #+#             */
/*   Updated: 2025/04/29 17:46:13 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal;

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

static void	display_prompt(void)
{
	char	*home;
	char	*cwd;
	char	*relative_path;

	home = getenv("HOME");
	cwd = getcwd(NULL, 0);
	if (home && cwd)
	{
		relative_path = ft_strstr(cwd, home);
		if (relative_path)
			printf("\033[1;33m╭─[\033[1;35m~%s\033[1;33m]\n╰─➤ \033[0m",
				relative_path + ft_strlen(home));
		else
			printf("\033[1;33m╭─[\033[1;35m%s\033[1;33m]\n╰─➤ \033[0m", cwd);
	}
	else
		printf("\033[1;33m╭─[\033[1;35munknown\033[1;33m]\n╰─➤ \033[0m");
	free(cwd);
}
// ft_strstr finds the first occurrence of home in cwd

static char	*get_user_input(void)
{
	char	*input;
	ssize_t	read;

	input = NULL;
	read = getline(&input, &(size_t){0}, stdin);
	if (read == -1)
	{
		free(input);
		return (NULL);
	}
	if (input[read - 1] == '\n')
		input[read - 1] = '\0';
	return (input);
} //FONCTION TEMPORAIRE (SERA REMPLACE PAR LA PARTIE PARSING)


static char	**create_arguments(t_token *token)
{
	char	**args;
	char	*temp;
	char	*token_str;
	int		count;

	temp = ft_strdup(token->str);
	count = 0;
	token_str = ft_strtok(temp, " ");
	while (token_str && ++count)
		token_str = ft_strtok(NULL, " ");
	free(temp);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	temp = ft_strdup(token->str);
	token_str = ft_strtok(temp, " ");
	count = 0;
	while (token_str)
	{
		args[count++] = ft_strdup(token_str);
		token_str = ft_strtok(NULL, " ");
	}
	args[count] = NULL;
	free(temp);
	return (args);
} //FONCTION TEMPORAIRE (SERA REMPLACE PAR LA PARTIE PARSING)

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
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
} //FONCTION TEMPORAIRE (SERA REMPLACE PAR LA PARTIE PARSING)

static char	*find_command_path(const char *cmd)
{
	char	*path;
	char	*dir;
	char	*full_path;
	char	*path_copy;

	if (!cmd || !*cmd || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = getenv("PATH");
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
// tester tous les path jusqu'a trouver le bon

static void	execute_command(t_token *tokens)
{
	pid_t		pid;
	char		**args;
	char		*cmd_path;
	extern char	**environ;

	pid = fork();
	if (pid == 0)
	{
		args = create_arguments(tokens);
		if (!args || !args[0])
			exit(1);
		cmd_path = find_command_path(args[0]);
		if (!cmd_path)
		{
			ft_putstr_fd("\033[1;31mError: command not found: \033[0m", 2);
			ft_putendl_fd(args[0], 2);
			ft_free_array(args);
			exit(127);
		}
		execve(cmd_path, args, environ);
		perror("\033[1;31mError\033[0m");
		free(cmd_path);
		ft_free_array(args);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		wait(NULL);
}

int	main(void)
{
	char	*input;
	t_token	*tokens;

	while (1)
	{
		display_prompt();
		input = get_user_input();
		if (!input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		tokens = malloc(sizeof(t_token));
		tokens->str = ft_strdup(input);
		tokens->type = CMD;
		tokens->quote = NONE;
		tokens->next = NULL;
		tokens->prev = NULL;
		execute_command(tokens);
		free_tokens(tokens);
		free(input);
	}
	return (0);
}
