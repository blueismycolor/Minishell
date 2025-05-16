/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing0_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:53:24 by aeudes            #+#    #+#             */
/*   Updated: 2025/05/16 17:54:53 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_input(char *input)
{
	if (!validate_input(input))
		return (ERROR);
	return (SUCCESS);
}

bool	validate_input(char *input)
{
	if (!check_pipe_syntax(input, 0))
		return false;
	if (!check_quote_syntax(input, 0))
		return false;
	if (!check_redirection_syntax(input, 0))
		return false;
	return true;
}

bool	check_pipe_syntax(char *input, int i)
{
	int		j;
	char	quote;

	quote = 0;
	if (input[0] == '|')
		return (ft_putstr_fd(ERR_SYN, STDERR_FILENO), false);
	while (input[i])
	{
		if((input[i] == '\'' || input[i] == '\"') && quote == 0)
			quote = input[i];
		else if (input[i] == quote)
			quote = 0;
		if (quote == 0 && input[i] =='|')
		{
			if (input[i + 1] == '\0')
				return (ft_putstr_fd(ERR_SYN, STDERR_FILENO), false);
			j = i + 1;
			while (input[j] == ' ')
				j++;
			if (input[j] == '|')
				return (ft_putstr_fd(ERR_SYN, STDERR_FILENO), false);
		}
		i++;
	}
	return (true);
}


int	check_quote_syntax(char *input, int i)
{
	while (input[i] && input[i] != '|' && input[i] != '>' && input[i] != '<')
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i] == '\0')
				return (ft_putstr_fd(OPEN_SNG_QUOTE, STDERR_FILENO), ERROR);
		}
		else if (input[i] == '\"')
		{
			i++;
			while (input[i]  && input[i] != '\"')
				i++;
			if (input[i] == '\0')
				return (ft_putstr_fd(OPEN_DBL_QUOTE, STDERR_FILENO), ERROR);
		}
		i++;
	}
	return (i);
}
bool		check_redirection_syntax(char *input, int i)
{
	int	j;


	while (input[i])
	{
		if ((input[i] == '<' || input[i] == '>') && !is_in_quotes(input, i)
			&& !is_in_double_quotes(input, i))
		{
			if ((input[i] == '<' && input[i + 1] == '>')
				|| (input[i] == '>' && input[i + 1] == '<')
				|| (input[i] == '<' && input[i + 1] == '<'
					&& (input[i + 2] == '<' || input[i + 2] == '>'))
				|| (input[i] == '>' && input[i + 1] == '>'
					&& (input[i + 2] == '<' || input[i + 2] == '>')))
					return (ft_putstr_fd(ERR_SYN, STDERR_FILENO), false);
				j = i + 1;
				while (input[j] || input[j] == ' ')
					j++; 
				if (input[j] == '\0' || input[j] == '<' || input[j] == '>' || input[j] == '|')
					return (ft_putstr_fd(ERR_SYN, STDERR_FILENO), false);
		}
		i++;
	}
	return (true);
}