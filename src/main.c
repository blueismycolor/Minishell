/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:31:27 by egatien           #+#    #+#             */
/*   Updated: 2025/06/19 13:39:39 by egatien          ###   ########.fr       */
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

void	free_data(t_data *data)
{
	free(data->pwd);
	free_tab(data->env);
	free(data);
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

int	main(int argc, char **argv, char **envp)
{
	t_data				*data;
	struct sigaction	sa_quit;
	int					return_value;

	(void)argc;
	(void)argv;
	g_signal = 0;
	disable_echoctl();
	data = init_data(envp);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	init_history(data);
	main_loop(data);
	free_history(data);
	return_value = data->return_value;
	free_data(data);
	exit(return_value);
	return (0);
}
