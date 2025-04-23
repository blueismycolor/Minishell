/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:57:58 by aeudes            #+#    #+#             */
/*   Updated: 2025/03/04 12:38:12 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (sign * result);
}
/*int	main(void)
{
	char	str1[] = "  12345";
	char	str2[] = "-123456";
	char	str3[] = "3456sdg";

	printf ("%d\n", ft_atoi(str1));
	printf ("%d\n", ft_atoi(str2));
	printf ("%d\n", ft_atoi(str3));
	printf ("%d\n", atoi(str1));
	printf ("%d\n", atoi(str2));
	printf ("%d\n", atoi(str3));
	return (0);
}*/