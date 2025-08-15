/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:53:22 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:53:24 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned const char	*cast_s;
	unsigned char		*cast_d;
	size_t				i;

	cast_d = (unsigned char *)dest;
	cast_s = (unsigned const char *)src;
	if (!dest && !src)
		return (NULL);
	if (cast_d < cast_s)
	{
		i = 0;
		while (i < n)
		{
			cast_d[i] = cast_s[i];
			i++;
		}
	}
	else
	{
		while (n--)
			cast_d[n] = cast_s[n];
	}
	return (dest);
}
/*int	main(void)
{
    // 1. Test - Basit kopyalama
    char dest1[50] = "Hello, World!";
    char src1[] = "Goodbye";
    printf("Original dest1: %s\n", dest1);
    ft_memmove(dest1, src1, 7);
    printf("After ft_memmove dest1: %s\n\n", dest1);

    // 2. Test - Üst üste binmeyen alanlar
    char dest2[50] = "abcdefgh";
    char src2[] = "123456";
    printf("Original dest2: %s\n", dest2);
    ft_memmove(dest2 + 2, src2, 6);  // dest2'nin ortasına src2 kopyalanacak
    printf("After ft_memmove dest2: %s\n\n", dest2);

    // 3. Test - Üst üste binen alanlar (sağdan sola kopyalama)
    char dest3[] = "Overlap test case";
    printf("Original dest3: %s\n", dest3);
    ft_memmove(dest3 + 5, dest3, 10)

    // 4. Test - Üst üste binen alanlar (soldan sağa kopyalama)
    char dest4[] = "Another overlap example";
    printf("Original dest4: %s\n", dest4);
    ft_memmove(dest4, dest4 + 8, 15)

    // 5. Test - Kaynak veya hedef NULL ise
    char *dest5 = NULL;
    char *src5 = "NULL check";
    char *result = ft_memmove(dest5, src5, 5);
    if (result == NULL)
        printf("ft_memmove handled NULL input correctly.\n");

    return (0);
}*/