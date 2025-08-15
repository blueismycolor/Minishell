/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:53:08 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:53:10 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *pointeur, int value, size_t count)
{
	char	*temps;
	size_t	i;

	temps = (char *) pointeur;
	i = 0;
	while (i < count)
	{
		temps[i] = value;
		i++;
	}
	return (pointeur);
}
/*int	main(void)
{
	char str[] = "545457466";

	ft_memset(str, 'x', 5);
	printf("%s\n", str);
	return (0);
}*/