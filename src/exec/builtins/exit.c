/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:33:56 by mgodefro          #+#    #+#             */
/*   Updated: 2025/06/16 13:46:14 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_exit(t_data *data, char *input)
{
	if (!input || ft_strcmp(input, "exit") == 0)
	{
		close(data->saved_stdin);
		close(data->saved_stdout);
		printf("exit\n\033[1;31m(╯°□°)╯︵ ┻━┻\033[0m\n");
		data->is_exit = true;
		return (1);
	}
	return (0);
}
