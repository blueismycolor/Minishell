/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximegdfr <maximegdfr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:31:27 by egatien           #+#    #+#             */
/*   Updated: 2025/06/04 16:10:36 by maximegdfr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal;

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
	printf("\033[1;92m[\033[1;35m");
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
	g_signal = sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	print_prompt_header();
	rl_redisplay();
}

char	**create_arguments(t_cmd *token)
{
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
}

void	execute_command(t_data *data)
{
	pid_t		pid;
	extern char	**environ;
	int			status;

	status = 0;
	pid = fork();
	if (pid == 0)
		process(data, environ);
	else if (pid > 0)
		exit_process(data, pid, status);
}

static void	main_loop(t_data *data)
{
	char		*input;

	while (1)
	{
		signal(SIGINT, sigint_handler);
		input = NULL;
		if (!g_signal)
		{
			print_prompt_header();
			input = readline("\001\033[1;92m\002minishell> \001\033[0m\002");
		}
		data->saved_stdin = dup(STDIN_FILENO);
		data->saved_stdout = dup(STDOUT_FILENO);
		g_signal = 0;
		handle_exit(data, input);
		data->cmd = tcmd_init(input, data);
		// print_data(data);
		if (data->cmd == NULL && !data->is_exit)
		{
			free(input);
			continue ;
		}
		if (!data->is_exit)
		{
			if (data->cmd->next)
				handle_pipes(data);
			else if (handle_redir(data))
			{
				if (data->cmd->is_builtin)
					select_builtin(data);
				else
					execute_command(data);
			}
		}
		reset_fd(data);
		if (ft_strlen(input) > 0 && !data->is_exit)
			add_to_history(data, input);
		free_tcmd(data->cmd);
		free(input);
		if (data->is_exit)
			break ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_data		*data;

	g_signal = 0;
	disable_echoctl();
	data = init_data(envp);
	struct sigaction sa_quit;
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	init_history(data);
	main_loop(data);
	free_history(data);
	return (0);
}
