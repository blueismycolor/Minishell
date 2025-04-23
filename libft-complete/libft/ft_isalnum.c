/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:57:13 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:57:17 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int verif)
{
	if ((verif >= 'a' && verif <= 'z') || (verif >= 'A' && verif <= 'Z')
		|| (verif >= '0' && verif <= '9'))
		return (1);
	return (0);
}

/*int	main(void)
{
	int test = 'a';
	int test1 = 'A';
	int test2 = '1';
	int test3 = '/';

	printf ("%d", ft_isalnum(test));
	printf ("%d", ft_isalnum(test1));
	printf ("%d", ft_isalnum(test2));
	printf ("%d", ft_isalnum(test3));
	return (0);
}*/