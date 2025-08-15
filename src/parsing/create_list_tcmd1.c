/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_tcmd1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:07:19 by aeudes            #+#    #+#             */
/*   Updated: 2025/08/15 09:20:14 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*give_isbuiltin(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (current->args && current->args[0]
			&& ((ft_strcmp(current->args[0], "cd") == 0)
				|| (ft_strcmp(current->args[0], "echo") == 0)
				|| (ft_strcmp(current->args[0], "env") == 0)
				|| (ft_strcmp(current->args[0], "export") == 0)
				|| (ft_strcmp(current->args[0], "pwd") == 0)
				|| (ft_strcmp(current->args[0], "unset") == 0)
				|| (ft_strcmp(current->args[0], "exit") == 0)))
			current->is_builtin = true;
		else
			current->is_builtin = false;
		current = current->next;
	}
	return (cmd);
}

char	**remove_filename(char **args)
{
	char	**tab;
	int		i;
	int		index;

	i = 0;
	index = 1;
	while (args[i])
		i++;
	tab = malloc(sizeof(char *) * i);
	i = 0;
	while (args[index])
	{
		tab[i] = ft_strdup(args[index]);
		i++;
		index++;
	}
	free_tab(args);
	tab[i] = NULL;
	return (tab);
}

void	fill_cmd_from_tokens(t_cmd *cmd, t_token **token)
{
	while (*token && (*token)->type != PIPE)
	{
		if ((*token)->type == CMD)
			add_arg(cmd, (*token)->str);
		else if ((*token)->type == INPUT
			|| (*token)->type == HEREDOC || (*token)->type == TRUNC
			|| (*token)->type == APPEND)
		{
			if ((*token)->next)
			{
				add_redir(cmd, (*token)->next->str, (*token)->type);
				*token = (*token)->next;
			}
		}
		*token = (*token)->next;
	}
}

t_cmd	*fill_special_cmd(t_token **tokens,
	t_cmd **head, t_cmd **last, t_cmd **new_cmd)
{
	char	**args;

	args = set_args((*tokens)->next->str);
	(*new_cmd) = init_cmd_node(head, last);
	if (!(*new_cmd))
		return (NULL);
	add_redir((*new_cmd), args[0], (*tokens)->type);
	*tokens = (*tokens)->next->next;
	(*new_cmd)->args = remove_filename(args);
	while ((*tokens) && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == INPUT || (*tokens)->type == HEREDOC
			|| (*tokens)->type == TRUNC || (*tokens)->type == APPEND)
		{
			if ((*tokens)->next)
			{
				add_redir((*new_cmd), (*tokens)->next->str, (*tokens)->type);
				*tokens = (*tokens)->next;
			}
		}
		*tokens = (*tokens)->next;
	}
	if (*tokens)
		*tokens = (*tokens)->next;
	return ((*new_cmd));
}

t_cmd	*create_list_tcmd(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*last;
	t_cmd	*new_cmd;

	head = NULL;
	last = NULL;
	new_cmd = NULL;
	while (tokens)
	{
		while (tokens && (tokens->type == INPUT || tokens->type == HEREDOC
				|| tokens->type == TRUNC || tokens->type == APPEND))
		{
			fill_special_cmd(&tokens, &head, &last, &new_cmd);
			new_cmd = new_cmd->next;
		}
		if (!tokens)
			break ;
		new_cmd = init_cmd_node(&head, &last);
		if (!new_cmd)
			return (NULL);
		fill_cmd_from_tokens(new_cmd, &tokens);
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (head);
}
