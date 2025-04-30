/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:31:27 by egatien           #+#    #+#             */
/*   Updated: 2025/04/30 14:24:57 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal;

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

static char	*get_prompt(void)
{
	char	*cwd;
	char	*home;
	char	*prompt;
	char	*relative;
	int		len;

	cwd = getcwd(NULL, 0);
	home = getenv("HOME");
	len = ft_strlen("\033[1;92m╭─[\033[1;35m") + ft_strlen("\033[1;92m]\n╰─➤ \033[0m");
	if (cwd)
	{
		if (home && (relative = ft_strnstr(cwd, home, ft_strlen(cwd))))
		{
			relative += ft_strlen(home);
			len += ft_strlen(relative) + 1; // +1 pour le ~
		}
		else
			len += ft_strlen(cwd);
	}
	else
		len += ft_strlen("unknown");
	prompt = malloc(len + 1);
	if (!prompt)
		return (NULL);
	ft_strlcpy(prompt, "\033[1;92m╭─[\033[1;35m", len + 1);
	if (cwd)
	{
		if (home && relative)
			ft_strlcat(prompt, "~", len + 1);
		ft_strlcat(prompt, (relative ? relative : cwd), len + 1);
	}
	else
		ft_strlcat(prompt, "unknown", len + 1);
	ft_strlcat(prompt, "\033[1;92m]\n╰─➤ \033[0m", len + 1);
	free(cwd);
	return (prompt);
}

int	main(void)
{
	char	*input;
	char 	*prompt;
	t_token	*tokens;

	while (1)
	{
		prompt = get_prompt();
		input = readline(prompt);
		free(prompt);
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
