/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 12:10:32 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 12:10:39 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int verif)
{
	if ((verif >= 'a' && verif <= 'z') || (verif >= 'A' && verif <= 'Z'))
		return (1);
	return (0);
}
/*int	main(void)
{
	char test = 'h';
	char test1 = 'H';
	char test2 = '2';
	char test3 = '/';

	printf("%d", ft_isalpha(test));
	printf("%d", ft_isalpha(test1));
	printf("%d", ft_isalpha(test2));
	printf("%d", ft_isalpha(test3));

	return (0);
}*/