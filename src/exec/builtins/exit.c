/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:33:56 by mgodefro          #+#    #+#             */
/*   Updated: 2025/05/14 12:38:58 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_exit(t_data *data, char *input)
{
//	printf("ENTRY HANDLE_EXIT\n");
	if (!input || ft_strcmp(input, "exit") == 0)
	{
		if (data)
			free(data);
		if (input)
			free(input);
		printf("exit\n\033[1;31m(╯°□°)╯︵ ┻━┻\033[0m\n");
		return (1);
	}
	return (0);
}
