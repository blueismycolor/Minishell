/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 12:03:17 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 12:03:35 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*cast1;
	unsigned char	*cast2;

	cast1 = (unsigned char *)s1;
	cast2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (cast1[i] != cast2[i])
			return (cast1[i] - cast2[i]);
		i++;
	}
	return (0);
}
/*int	main(void)
{
	char	str1[] = "";
	char	str2[] = "";
	char	str3[] = "hello comment";
	printf("%d\n", ft_memcmp(str1,str2,0));
	printf("%d\n", ft_memcmp(str2,str3,2));
	return (0);
}*/	