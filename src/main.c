/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:31:27 by egatien           #+#    #+#             */
/*   Updated: 2025/08/15 12:43:56 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal;

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
	if (data->old_pwd)
		free(data->old_pwd);
	free(data->pwd);
	free_history(data);
	free_tab(data->env);
	free(data);
}

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		print_prompt_header();
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data				*data;
	struct sigaction	sa_quit;
	int					return_value;

	(void)argc;
	(void)argv;
	g_signal = 0;
	data = init_data(envp);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	init_history(data);
	main_loop(data);
	return_value = data->return_value;
	free_data(data);
	exit(return_value);
	return (0);
}
