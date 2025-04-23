/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:48:26 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:48:27 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	char	*newstr;
	size_t	i;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_strdup(""));
	if (start + len > len_s)
		len = len_s - start;
	newstr = (char *)malloc((len + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		newstr[i] = s[start + i];
		i++;
	}
	newstr[len] = '\0';
	return (newstr);
}
/*int	main(void)
{
	char	str[] = "hello world";
	char	*result =  ft_substr(str, 20, 5); // Burada 'start' değeri çok büyük
	if (result)
	{
		printf("%s\n", result);
		free(result); // yalnızca NULL değilse serbest bırak
	}
	else
		printf("it didn't work");
	return (0);
}*/