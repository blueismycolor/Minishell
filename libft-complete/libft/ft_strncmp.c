/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:49:54 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:50:00 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < size)
	{
		if ((unsigned char) s1[i] != (unsigned char)s2[i])
			return ((unsigned char) s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*int	main(void)
{
	char	s1[] = "salut";
	char	s2[] = "halut";
	char	s3[] = "sapin";

	printf ("%d\n", ft_strncmp(s1,s2,3));
	printf ("%d\n", ft_strncmp(s1,s3,3));
	printf ("%d\n", ft_strncmp(s2,s3,3));
	return (0);
}*/