/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:37:04 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:37:20 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_print_str("(null)"));
	while (str[i])
		i += ft_print_char(str[i]);
	return (i);
}
/*int	main(void)
{
	char	str[] = "salut comment ca va";
	
	ft_print_str(str);
	printf ("%s\n", str);
	return (0);
}*/