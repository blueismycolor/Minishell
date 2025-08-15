/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:27:18 by tlair             #+#    #+#             */
/*   Updated: 2025/06/02 17:58:37 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_to_history(t_data *data, const char *input)
{
	if (!input || !*input || !data)
		return ;
	add_history(input);
	data->history = ft_extend_array(data->history, input);
}

void	init_history(t_data *data)
{
	data->history = NULL;
	rl_clear_history();
}

void	free_history(t_data *data)
{
	ft_free_array(data->history);
	data->history = NULL;
}
