/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:31:27 by egatien           #+#    #+#             */
/*   Updated: 2025/05/14 17:49:37 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal;

void	disable_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	print_prompt_header(void)
{
	char	*cwd;
	char	*home;
	char	*relative;

	cwd = getcwd(NULL, 0);
	home = getenv("HOME");
	relative = NULL;
	if (cwd && home)
	{
		relative = cwd;
		if (!ft_strncmp(cwd, home, ft_strlen(home)))
			relative += ft_strlen(home);
		else
			relative = NULL;
	}
	printf("\033[1;92m╭─[\033[1;35m");
	if (cwd && home && relative)
		printf("~%s", relative);
	else if (cwd)
		printf("%s", cwd);
	else
		printf("unknown");
	printf("\033[1;92m]\033[0m\n");
	free(cwd);
}

void	sigint_handler(int sig)
{
	(void)sig;
	g_signal = 1;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	print_prompt_header();
	rl_redisplay();
}

char	**create_arguments(t_cmd *token)
{ //FONCTION TEMPORAIRE (SERA REMPLACEE PAR LA PARTIE PARSING)
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
} //FONCTION TEMPORAIRE (SERA REMPLACEE PAR LA PARTIE PARSING)

static void	execute_command(t_cmd *cmd)
{
//	printf("ENTRY EXECUTE_COMMAND\n");
	pid_t		pid;
	char		*cmd_path;
	extern char	**environ;
	int			status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (!cmd->args || !cmd->args[0])
			exit(1);
		cmd_path = find_command_path(cmd->args[0]);
		if (!cmd_path)
		{
			msg_error("\033[1;31mcommand not found: \033[0m");
			ft_putendl_fd(cmd->args[0], 2);
			ft_free_array(cmd->args);
			exit(127);
		}
		execve(cmd_path, cmd->args, environ);
		perror("\033[1;31mError\033[0m");
		free(cmd_path);
		ft_free_array(cmd->args);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		signal(SIGINT, sigint_handler);
		waitpid(pid, &status, 0);
	}
}

void	select_builtin(t_data *data)
{
	if (!data->cmd || !data->cmd->cmd)
		msg_error("Invalid command.\n");
	if (ft_strncmp(data->cmd->cmd, "cd", 2) == 0)
		handle_cd(data);
	if (ft_strncmp(data->cmd->cmd, "echo", 4) == 0)
		handle_echo(data);
	if (ft_strncmp(data->cmd->cmd, "env", 3) == 0)
		handle_env(data);
	if (ft_strncmp(data->cmd->cmd, "export", 6) == 0)
		handle_export_var(data);
	if (ft_strncmp(data->cmd->cmd, "pwd", 3) == 0)
		handle_pwd(data);
	if (ft_strncmp(data->cmd->cmd, "unset", 5) == 0)
		handle_unset(data);
}

int	main(void)
{
	char		*input;
	extern char	**environ;
	t_data		*data;

	g_signal = 0;
	disable_echoctl();
	data = init_data(environ);
	init_history(data);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		input = NULL;
		if (!g_signal)
		{
			print_prompt_header();
			input = readline("\033[1;92m╰─➤ \033[0m");
		}
		g_signal = 0;
		if (handle_exit(data, input))
			break ;
		data->cmd = init_cmd(data->cmd, input);
//		print_data(data);

		if (data->cmd->is_builtin)
			select_builtin(data);
		else
			execute_command(data->cmd);
//		select_builtin(data, input);
		if (ft_strlen(input) > 0)
			add_to_history(data, input);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}

//		execute_command(data->cmd);
		free_tokens(data->cmd);
		free(input);
	}
	free_history(data);
	return (0);
}
