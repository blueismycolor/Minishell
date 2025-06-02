/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:33:56 by mgodefro          #+#    #+#             */
/*   Updated: 2025/05/30 14:28:27 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_exit(t_data *data, char *input)
{
	if (!input || ft_strcmp(input, "exit") == 0)
	{
		printf("exit\n\033[1;31m(╯°□°)╯︵ ┻━┻\033[0m\n");
		data->is_exit = true;
		return (1);
	}
	return (0);
}
