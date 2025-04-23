/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:37:40 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:37:54 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_int(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		count += write (1, "-2147483648", 11);
		return (count);
	}
	if (n < 0)
	{
		count += ft_print_char('-');
		n = -n;
	}
	if (n >= 10)
	{
		count += ft_print_int(n / 10);
		count += ft_print_int(n % 10);
	}
	if (n < 10)
		count += ft_print_char(n + '0');
	return (count);
}

/*int	main(void)
{
	int	nbr = -2147483648;
	printf ("%d\n", nbr);
	return (0);
}*/