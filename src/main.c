/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:31:27 by egatien           #+#    #+#             */
/*   Updated: 2025/04/30 12:15:46 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal;

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
			printf("\033[1;92m╭─[\033[1;35m~%s\033[1;92m]\n╰─➤ \033[0m",
				relative_path + ft_strlen(home));
		else
			printf("\033[1;92m╭─[\033[1;35m%s\033[1;92m]\n╰─➤ \033[0m", cwd);
	}
	else
		printf("\033[1;92m╭─[\033[1;35munknown\033[1;92m]\n╰─➤ \033[0m");
	free(cwd);
}
// ft_strstr finds the first occurrence of home in cwd

static char	*get_user_input(void)
{ //FONCTION TEMPORAIRE (SERA REMPLACE PAR LA PARTIE PARSING)
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
{ //FONCTION TEMPORAIRE (SERA REMPLACE PAR LA PARTIE PARSING)
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
			msg_error("\033[1;31mcommand not found: \033[0m");
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
			printf("\033[1;31m(╯°□°)╯︵ ┻━┻\033[0m\n");
			break ;
		}
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			printf("\033[1;31m(╯°□°)╯︵ ┻━┻\033[0m\n");
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
