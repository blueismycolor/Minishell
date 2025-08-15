/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:38:07 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:38:09 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hexa(unsigned int n, int casse)
{
	int		count;
	char	*base;

	count = 0;
	if (casse)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n >= 16)
	{
		count += ft_print_hexa(n / 16, casse);
		count += ft_print_char(base[n % 16]);
	}
	else
		count += ft_print_char(base[n]);
	return (count);
}

/*int	main(void)
{
	unsigned int n = 0x899BA;
	int	printed_chars = ft_print_hexa(n, 1);
	printf("\nprinted characters: %d\n", printed_chars);
	printf("original number in decimal: %u\n", n); 
	return (0);
}*/