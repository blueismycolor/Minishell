/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:48:11 by aeudes            #+#    #+#             */
/*   Updated: 2025/03/04 12:36:38 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int letter)
{
	if (letter >= 65 && letter <= 90)
		return (letter += 32);
	return (letter);
}
/*int	main(void)
{
	int	c;

	c = 'T';
	c = ft_tolower(c);
	printf("%c\n", c);
	return (0);
}*/