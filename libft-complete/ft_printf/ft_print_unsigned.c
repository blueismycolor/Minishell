/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:36:46 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:36:56 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
	{
		count += ft_print_unsigned(n / 10);
		count += ft_print_char((n % 10) + '0');
	}
	else
		count += ft_print_char(n + '0');
	return (count);
}

/*int	main(void)
{
	unsigned int	n = 1223456;
	
	printf("\nusing ft_print_unsigned:\n ");

	int	count = ft_print_unsigned(n);
	printf("\ncount returned: %d\n", count);
	printf("\nusing standard printf: \n");
	printf("%u\n", n);
	return (0);
}*/