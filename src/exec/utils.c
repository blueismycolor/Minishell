/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:45:43 by tlair             #+#    #+#             */
/*   Updated: 2025/05/14 12:40:28 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmd;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	ft_free_array(char **array)
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

void print_data(t_data *data)
{
	if (!data)
		return ;
    printf("\033[40m\n\t* DATA *\033[0m\n");
    printf("\tENV : %p\n", (void *)data->env);
    printf("\tPWD : %s\n", data->pwd ? data->pwd : "(null)");
    printf("\tOLD_PWD : %s\n", data->old_pwd ? data->old_pwd : "(null)");
    printf("\tRETURN_VALUE : %d\n", data->return_value);
	t_cmd *cmd = data->cmd;
	while (cmd)
	{
		printf("\n\033[40m\t\t* CMD *\033[0m\n");
		printf("\t\tCMD : %s\n", cmd->cmd ? cmd->cmd : "(null)");
		printf("\t\tBUILT IN : %s\n", cmd->is_builtin ? "true" : "false");
		for (int i = 0; cmd->args && cmd->args[i]; i++) {
			printf("\t\tARGS[%d] : %s\n", i, cmd->args[i]);
		}
		printf("\t\tNB PARAMS : %d\n", cmd->nb_params);
		printf("\t\tTYPE : %d\n", cmd->type);
		printf("\t\tREDIR : %s\n", cmd->has_redir ? "true" : "false");
		if (cmd->has_redir && cmd->redir)
		{
			t_redir *redir = cmd->redir;
			while (redir)
			{
				printf("\n\033[40m\t\t\t* REDIR *\033[0m\n");
				printf("\t\t\tFILENAME : %s\n", redir->filename ? redir->filename : "(null)");
				printf("\t\t\tTYPE : %d\n", redir->type);
				printf("\t\t\tNEXT : %p\n", (void *)redir->next);
				redir = redir->next;
			}
		}
		cmd = cmd->next;
	}
}
