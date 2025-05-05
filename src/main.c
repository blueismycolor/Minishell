/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:31:27 by egatien           #+#    #+#             */
/*   Updated: 2025/05/05 16:52:36 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal;

char	**create_arguments(t_cmd *token)
{ //FONCTION TEMPORAIRE (SERA REMPLACE PAR LA PARTIE PARSING)
	char	**args;
	char	*temp;
	char	*token_str;
	int		count;

	temp = ft_strdup(token->cmd);
	count = 0;
	token_str = ft_strtok(temp, " ");
	while (token_str && ++count)
		token_str = ft_strtok(NULL, " ");
	free(temp);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	temp = ft_strdup(token->cmd);
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

static void	execute_command(t_cmd *tokens)
{
	pid_t		pid;
	char		*cmd_path;
	extern char	**environ;

	pid = fork();
	if (pid == 0)
	{
		if (!tokens->args || !tokens->args[0])
			exit(1);
		cmd_path = find_command_path(tokens->args[0]);
		if (!cmd_path)
		{
			msg_error("\033[1;31mcommand not found: \033[0m");
			ft_putendl_fd(tokens->args[0], 2);
			ft_free_array(tokens->args);
			exit(127);
		}
		execve(cmd_path, tokens->args, environ);
		perror("\033[1;31mError\033[0m");
		free(cmd_path);
		ft_free_array(tokens->args);
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
	char		*input;
	char 		*prompt;
	extern char	**environ;
	t_data		*data;

	data = init_data(environ);
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
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		data->cmd = init_cmd(data->cmd, input);
		if (ft_strncmp(data->cmd->cmd, "cd", 2) == 0)
		{
			printf("Test function cd\n");
			handle_cd(data);
			continue ;
		}
		execute_command(data->cmd);
		free_tokens(data->cmd);
		free(input);
	}
	return (0);
}
