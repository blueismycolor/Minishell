/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:45:43 by tlair             #+#    #+#             */
/*   Updated: 2025/06/30 17:52:14 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_with_code(t_data *data, int exit_code)
{
	data->return_value = exit_code;
	exit(data->return_value);
}

void	free_tokens(t_data *data)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!data->is_exit)
	{
		current = data->cmd;
		while (current != NULL)
		{
			next = current->next;
			free(current);
			current = next;
		}
	}
}

void	ft_free_array(char **array) // pareille que free_tab
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	reset_fd(t_data *data)
{
	dup2(data->saved_stdin, STDIN_FILENO);
	dup2(data->saved_stdout, STDOUT_FILENO);
	close(data->saved_stdin);
	close(data->saved_stdout);
}

/*void	print_data(t_data *data)
{
	t_cmd *cmd;

	if (!data)
		return ;
	printf("\033[40m\n\t* DATA *\033[0m\n");
	printf("\tENV : %p\n", (void *)data->env);
	printf("\tPWD : %s\n", data->pwd ? data->pwd : "(null)");
	printf("\tOLD_PWD : %s\n", data->old_pwd ? data->old_pwd : "(null)");
	printf("\tRETURN_VALUE : %d\n", data->return_value);
	printf("\tSAVED_STDIN : %d\n", data->saved_stdin);
	printf("\tSAVED_STDOUT : %d\n", data->saved_stdout);
	if (data->cmd)
	{
		cmd = data->cmd;
		while (cmd)
		{
			printf("\n\033[40m\t\t* CMD *\033[0m\n");
			// if (cmd->cmd)
			// 	printf("\t\tCMD : %s\n", cmd->cmd);
			// else
			// 	printf("\t\tCMD : (null)\n");
			printf("\t\tBUILT IN : %s\n", cmd->is_builtin ? "true" : "false");
			for (int i = 0; cmd->args && cmd->args[i]; i++) {
				printf("\t\tARGS[%d] : %s\n", i, cmd->args[i]);
			}
			printf("\t\tNB PARAMS : %d\n", cmd->nb_params);
			// printf("\t\tTYPE : %d\n", cmd->type);
			printf("\t\tFD : %d\n", cmd->fd);
			printf("\t\tREDIR : %s\n", cmd->has_redir ? "true" : "false");
			if (cmd->has_redir && cmd->redir)
			{
				t_redir *redir = cmd->redir;
				while (redir)
				{
					printf("\n\033[40m\t\t\t* REDIR *\033[0m\n");
					printf("\t\t\tFILENAME : %s\n",
						redir->filename ? redir->filename : "(null)");
					printf("\t\t\tDEL : %s\n", redir->del ?
						redir->del : "(null)");
					printf("\t\t\tTYPE : %d\n", redir->type);
					printf("\t\t\tNEXT : %p\n", (void *)redir->next);
					redir = redir->next;
				}
			}
			cmd = cmd->next;
		}
	}
}*/
