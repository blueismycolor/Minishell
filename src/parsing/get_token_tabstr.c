/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_tabstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:35:29 by egatien           #+#    #+#             */
/*   Updated: 2025/06/25 13:49:47 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_redirections(char *str, int end)
{
	int	i;

	if ((str[end] == '>' && str[end + 1] == '>')
		|| (str[end] == '<' && str[end + 1] == '<'))
		i = end + 2;
	else
		i = end + 1;
	return (i);
}

char	**setup_variables(bool *command, int *j, int *i, char *str)
{
	char	**result;

	*command = false;
	*j = 0;
	*i = 0;
	result = malloc(sizeof(char *) * (get_nbr_tokens(str)+ 1));
	if (!result)
		return (NULL);
	return (result);
}

int	get_second_tokens(char *str, char **result, int *j, int end)
{
	if (str[end] != '\0')
	{
		result[*j] = put_second_tokens(str, end);
		(*j)++;
	}
	if (*j >= get_nbr_tokens(str))
	{
		result[*j] = NULL;
		return (0);
	}
	return (1);
}

/*
	fonction principale qui cherche les tokens
	dans la chaine de caracteres et les mets sous forme de tableaux de chaine
*/

char	**put_token_in_tabstr(char *str)
{
	char	**result;
	int		i;
	int		j;
	int		end;
	bool	command;

	result = setup_variables(&command, &j, &i, str);
	if (!result)
		return (NULL);
	while (str[i] != '\0')
	{
		while (ft_isspace(str[i]))
			i++;
		end = get_end_of_token(i, str, &command);
		if (command == true)
		{
			result[j] = get_str_token(str, i, end);
			j++;
		}
		if (!get_second_tokens(str, result, &j, end))
			break ;
		i = check_redirections(str, end);
	}
	return (result);
}

t_token	*get_token(char *str)
{
	t_token	*head;
	t_token	*node;
	char	**cut_str;
	int		i;

	i = 0;
	head = NULL;
	cut_str = put_token_in_tabstr(str);
	head = create_token(&head, cut_str[i],
			get_token_type(cut_str[i]), get_quote_type(cut_str[i]));
	head->has_expansion = check_for_expansion(head->str);
	node = head->next;
	free(cut_str[i]);
	i++;
	while (cut_str[i])
	{
		node = create_token(&head, cut_str[i],
				get_token_type(cut_str[i]), get_quote_type(cut_str[i]));
		node->has_expansion = check_for_expansion(node->str);
		node = node->next;
		free(cut_str[i]);
		i++;
	}
	free(cut_str);
	return (head);
}
