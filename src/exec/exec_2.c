/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:42:08 by mgodefro          #+#    #+#             */
/*   Updated: 2025/07/02 14:44:23 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_proc_sig_init(pid_t pid, int *status)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, status, 0);
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
				write(2, "Quit (core dumped)\n", 19);
			else
				write(2, "Quit\n", 5);
			data->return_value = 131;
		}
	}
	else if (WIFEXITED(status))
		data->return_value = WEXITSTATUS(status);
}
