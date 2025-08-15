/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:56:02 by aeudes            #+#    #+#             */
/*   Updated: 2025/06/27 14:29:32 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_args_and_filename(t_cmd *result,
		t_redir *redir, char **tab_redir)
{
	int		i;
	int		j;
	char	**args_cmd;

	i = 0;
	j = 1;
	redir->del = ft_strdup(tab_redir[0]);
	args_cmd = malloc(sizeof(char *)
			* (tab_size(tab_redir) + tab_size(result->args) + 1));
	while (result->args[i])
	{
		args_cmd[i] = ft_strdup(result->args[i]);
		i++;
	}
	if (!tab_redir[0])
		j--;
	while (tab_redir[j])
	{
		args_cmd[i] = ft_strdup(tab_redir[j]);
		j++;
		i++;
	}
	args_cmd[i] = NULL;
	free_tab(result->args);
	result->args = args_cmd;
}

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	check_for_args_in_redirection(t_cmd *result)
{
	while (result)
	{
		if (result->redir)
			add_args_in_redir(result);
		result = result->next;
	}
}

void	add_args_in_redir(t_cmd *result)
{
	char	**tab_redir;
	t_redir	*redir;

	redir = result->redir;
	while (redir)
	{
		tab_redir = set_args(redir->del);
		if (!tab_redir)
			continue ;
		if (tab_size(tab_redir) == 1)
		{
			free(redir->del);
			redir->del = ft_strdup(tab_redir[0]);
			free_tab(tab_redir);
			redir = redir->next;
			continue ;
		}
		free(redir->del);
		change_args_and_filename(result, redir, tab_redir);
		redir = redir->next;
		free_tab(tab_redir);
	}
}
