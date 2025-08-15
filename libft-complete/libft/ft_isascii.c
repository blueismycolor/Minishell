/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:56:46 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:56:48 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int verif)
{
	if (verif < 0 || verif > 127)
		return (0);
	return (1);
}
/*int	main(void)
{
	int test = ' ';
	int test1 = '\0';
	int test2 = 'a';
	int test3 = '4';

	printf("%d", ft_isalpha(test));
	printf("%d", ft_isalpha(test1));
	printf("%d", ft_isalpha(test2));
	printf("%d", ft_isalpha(test3));
	return (0);
}*/