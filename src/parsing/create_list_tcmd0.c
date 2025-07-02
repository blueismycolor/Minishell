/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_tcmd0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:08:52 by aeudes            #+#    #+#             */
/*   Updated: 2025/07/02 18:10:30 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*tcmd_init(char *input, t_data *data)
{
	t_token	*arg_tokens;
	t_cmd	*result;

	last_exit_status(data->return_value);
	if (!input || parsing_input(input, data) == -1)
		return (NULL);
	input = set_env(input, data->env);
	if (!input || !input[0])
	{
		free(input);
		return (NULL);
	}
	arg_tokens = get_token(input);
	if (!arg_tokens)
		return (NULL);
	result = create_list_tcmd(arg_tokens);
	check_for_args_in_redirection(result);
	result = give_isbuiltin(result);
	add_cmd_to_result(result);
	free_list(arg_tokens);
	free(input);
	return (result);
}

t_cmd	*init_cmd_node(t_cmd **cmd_list, t_cmd **current)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->is_builtin = false;
	new->args = NULL;
	new->nb_params = 0;
	new->has_redir = false;
	new->redir = NULL;
	new->next = NULL;
	new->prev = NULL;
	if (!*cmd_list)
		*cmd_list = new;
	else
	{
		(*current)->next = new;
		new->prev = *current;
	}
	*current = new;
	return (new);
}

char	**realloc_args(char **args, int size)
{
	char	**new_args;
	int		i;

	i = 0;
	new_args = malloc(sizeof(char *) * (size + 2));
	if (!new_args)
		return (NULL);
	while (i < size)
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[size] = NULL;
	free(args);
	return (new_args);
}

void	add_arg(t_cmd *cmd, char *str)
{
	cmd->args = set_args(str);
	if (!cmd->args)
		return ;
	if (!cmd->cmd)
		cmd->cmd = cmd->args[0];
}

void	add_redir(t_cmd *cmd, char *del, t_type type)
{
	t_redir	*new;
	t_redir	*tmp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	if (type == HEREDOC)
		new->filename = generate_heredoc_filename();
	else
		new->filename = NULL;
	new->del = ft_strdup(del);
	new->type = type;
	new->fd = -1;
	new->next = NULL;
	if (!cmd->redir)
		cmd->redir = new;
	else
	{
		tmp = cmd->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	cmd->has_redir = true;
}
