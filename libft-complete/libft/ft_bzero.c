/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:57:39 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:57:40 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*cast;
	size_t	i;

	cast = (char *)s;
	i = 0;
	while (i < n)
	{
		cast[i] = 0;
		i++;
	}
}
/*int	main(void)
{
	int	tab[] = {'a','w','e','u','v'};
	size_t	i;
	
	ft_bzero(tab,3*sizeof(int));
	i = 0;
	while (i < 3)
	{
		printf("%d ", tab[i]);
		i++;
	}
	printf("\n");
	return (0);
}*/