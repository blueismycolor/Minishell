/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:53:47 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:53:48 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	convert_c;
	size_t			i;

	str = (unsigned char *)s;
	convert_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == convert_c)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
/*int	main(void)
{
	char	str[] = "salut comment ca va";
	char	value;
	size_t	nbr;
	char	*result;

	value = 't';
	nbr = 5 ;
	result = ft_memchr(str,value,nbr);
	if (!result)
		return (1);
	printf("position[%ld]-value:%c\n-adresse:%p",result-str,value,&value);
	return (0);
}*/