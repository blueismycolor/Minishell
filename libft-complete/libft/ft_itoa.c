/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:56:08 by aeudes            #+#    #+#             */
/*   Updated: 2025/03/04 12:39:18 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_size(long long int nbr)
{
	int	size;

	size = 0;
	if (nbr <= 0)
	{
		nbr = nbr * -1;
		size++;
	}
	while (nbr != '\0')
	{
		size++;
		nbr = nbr / 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*res;
	long	temps;
	int		size;

	temps = n;
	size = ft_check_size(temps);
	res = (char *)malloc(size + 1 * sizeof(char));
	if (!res)
		return (NULL);
	res[size] = '\0';
	if (temps < 0)
	{
		temps = temps * -1;
		res[0] = '-';
	}
	--size;
	while (size >= (n < 0))
	{
		res[size--] = (temps % 10) + '0';
		temps = temps / 10;
	}
	return (res);
}
/*int	main(void)
{
	char	*res;

	res = ft_itoa(45);
	if(res)
	{
		printf("%s\n", res);
	}
	free(res);
	return (0);
}*/