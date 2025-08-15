/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:57:24 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:57:28 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementcount, size_t elementsize)
{
	void	*tab;

	tab = malloc(elementcount * elementsize);
	if (!tab)
		return (NULL);
	ft_bzero(tab, elementcount * elementsize);
	return (tab);
}
/*int	main(void)
{
	size_t	*result;
	size_t	count;
	size_t	size;
	size_t 	i;

	count = 5;
	size = 5;
	result = ft_calloc(count, size);
	if (!result)
		return(1);
	i = 0;
	while (i < count)
	{
		printf("adress[%zu]: %ld \n", i, result[i]);
		i++;
	}
	return (0);
}*/