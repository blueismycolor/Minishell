/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:56:20 by aeudes            #+#    #+#             */
/*   Updated: 2025/03/04 12:38:01 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int verif)
{
	if (verif >= 32 && verif <= 126)
		return (1);
	else
		return (0);
}
/*int	main(void)
{
	int test = '\0';
	int test1 = 'a';
	int test2 = '2';

	printf("%d", ft_isprint(test));
	printf("%d", ft_isprint(test1));
	printf("%d", ft_isprint(test2));
	return (0);
}*/