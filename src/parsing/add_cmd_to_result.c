/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_to_result.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:56:00 by egatien           #+#    #+#             */
/*   Updated: 2025/06/20 11:12:01 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_cmd_to_result(t_cmd *result)
{
	while (result)
	{
		result->cmd = result->args[0];
		result = result->next;
	}
}
