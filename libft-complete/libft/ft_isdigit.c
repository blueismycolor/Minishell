/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:56:33 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:56:37 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int verif)
{
	if (verif >= '0' && verif <= '9')
		return (1);
	return (0);
}
/*int	main(void)
{
	int test;
	int test2;
	int test3;


	test  = '1';
	test2 = 'a';
	test3 = '/';

	printf("%d", ft_isdigit(test));
	printf("%d", ft_isdigit(test2));
	printf("%d", ft_isdigit(test3));
	return (0);
}*/