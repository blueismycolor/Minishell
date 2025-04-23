/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:03:26 by mgodefro          #+#    #+#             */
/*   Updated: 2025/04/23 17:04:23 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msg_error(char *msg)
{
	ft_putstr_fd("./minishell: error:", 2);
	ft_putstr_fd(msg, 2);
	return ;
}
