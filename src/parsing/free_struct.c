/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:21:09 by aeudes            #+#    #+#             */
/*   Updated: 2025/06/30 14:12:06 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_list(t_token *head)
{
	t_token	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->str);
		free(temp);
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_redir(t_redir *redirection)
{
	t_redir	*temp;

	while (redirection)
	{
		temp = redirection;
		redirection = redirection->next;
		free(temp->del);
		free(temp->filename);
		free(temp);
	}
}

void	free_tcmd(t_cmd *list)
{
	t_cmd	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->args)
			free_tab(temp->args);
		if (temp->has_redir == true)
			free_redir(temp->redir);
		free(temp);
	}
}
