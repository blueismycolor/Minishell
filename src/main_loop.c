/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:23:37 by tlair             #+#    #+#             */
/*   Updated: 2025/06/16 14:26:59 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cleanup_main_loop(t_data *data, char *input)
{
	reset_fd(data);
	if (ft_strlen(input) > 0 && !data->is_exit)
		add_to_history(data, input);
	free_tcmd(data->cmd);
	free(input);
}

char	*init_main_loop_iteration(t_data *data)
{
	char	*input;

	input = NULL;
	signal(SIGINT, sigint_handler);
	if (!g_signal)
	{
		print_prompt_header();
		input = readline("\001\033[1;92m\002minishell> \001\033[0m\002");
	}
	data->saved_stdin = dup(STDIN_FILENO);
	data->saved_stdout = dup(STDOUT_FILENO);
	g_signal = 0;
	return (input);
}

void	main_loop(t_data *data)
{
	char	*input;

	while (!data->is_exit)
	{
		input = init_main_loop_iteration(data);
		handle_exit(data, input);
		if (!process_input(data, input))
		{
			add_to_history(data, input);
			free(input);
			continue ;
		}
		// print_data(data);
		if (!data->is_exit)
			execute_commands(data);
		cleanup_main_loop(data, input);
	}
}
