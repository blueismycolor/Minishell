/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:56:31 by aeudes            #+#    #+#             */
/*   Updated: 2025/06/27 12:42:29 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parsing_input(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '\0')
		return (ERROR);
	if (!validate_input(input, data))
		return (ERROR);
	return (SUCCESS);
}

bool	validate_input(char *input, t_data *data)
{
	if (!check_pipe_syntax(input, data, 0))
		return (false);
	if (check_quote_syntax(input, data, 0) == ERROR)
		return (false);
	if (!check_redirection_syntax(input, data, 0, 0))
		return (false);
	return (true);
}

bool	check_pipe_syntax(char *input, t_data *data, int i)
{
	int		j;
	char	quote;

	quote = 0;
	i = skip_space(input, 0);
	if (input[i] == '|')
		return (error(data, ERR_SYN, 2), false);
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && quote == 0)
			quote = input[i];
		else if (input[i] == quote)
			quote = 0;
		if (quote == 0 && input[i] == '|')
		{
			j = i + 1;
			j = skip_space(input, j);
			while (input[j] == '|' || input[j] == '\0')
				return (error(data, ERR_SYN, 2), false);
		}
		i++;
	}
	return (true);
}

int	check_quote_syntax(char *input, t_data *data, int i)
{
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
				i++;
			if (!input[i])
				return (error(data, OPEN_SNG_QUOTE, 2), ERROR);
		}
		else if (input[i] == '\"')
		{
			i++;
			while (input[i] && input[i] != '\"')
				i++;
			if (!input[i])
				return (error(data, OPEN_DBL_QUOTE, 2), ERROR);
		}
		i++;
	}
	return (i);
}

bool	check_redirection_syntax(char *input, t_data *data, int i, int j)
{
	while (input[i])
	{
		if ((input[i] == '<' || input[i] == '>')
			&& !is_in_quotes(input, i) && !is_in_double_quotes(input, i))
		{
			if ((input[i] == '<' && input[i + 1] == '>')
				|| (input[i] == '>' && input[i + 1] == '<')
				|| (input[i] == '<' && input[i + 1] == '<'
					&& (input[i + 2] == '<' || input[i + 2] == '>'))
				|| (input[i] == '>' && input[i + 1] == '>'
					&& (input[i + 2] == '<' || input[i + 2] == '>')))
				return (error(data, ERR_SYN, 2), false);
			if (input[i + 1] == '<' || input[i + 1] == '>')
				i++;
			j = i + 1;
			while (input[j] && ft_isspace(input[j]))
				j++;
			if (!input[j] || input[j] == '<'
				|| input[j] == '>' || input[j] == '|')
				return (error(data, ERR_SYN, 2), false);
		}
		i++;
	}
	return (true);
}
