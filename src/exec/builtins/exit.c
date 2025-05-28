/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:33:56 by mgodefro          #+#    #+#             */
/*   Updated: 2025/05/28 15:49:48 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_exit(t_data *data, char *input)
{
//	printf("ENTRY HANDLE_EXIT\n");
	if (!input || ft_strcmp(input, "exit") == 0)
	{
		printf("exit\n\033[1;31m(╯°□°)╯︵ ┻━┻\033[0m\n");
		data->is_exit = true;
		return (1);
	}
	return (0);
}
