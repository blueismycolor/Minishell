/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_tcmd0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:08:52 by aeudes            #+#    #+#             */
/*   Updated: 2025/06/12 08:01:26 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*tcmd_init(char *input, t_data *data)
{
	t_token	*arg_tokens;
	t_cmd	*result;

	last_exit_status(data->return_value);
	if (!input || parsing_input(input) == -1)
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
	result = give_isbuiltin(result);
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
	new->quote = NONE;
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
	char	*temp;

	temp = ft_remove_quotes(ft_strdup(del));
	new = malloc(sizeof(t_redir));
	if (!new || !temp)
		return ;
	if (type == HEREDOC)
		new->filename = generate_heredoc_filename();
	else
		new->filename = NULL;
	new->del = temp;
	new->type = type;
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
