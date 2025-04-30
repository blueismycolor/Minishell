/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:33:56 by mgodefro          #+#    #+#             */
/*   Updated: 2025/04/30 15:14:55 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_exit(t_data *data, char *input)
{
	if (ft_strcmp(input, "exit") == 0)
	{
		if (data)
			free(data);
		free(input);
		printf("\033[1;31m(╯°□°)╯︵ ┻━┻\033[0m\n");
	}
}
