/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbprk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:29:57 by tlair             #+#    #+#             */
/*   Updated: 2025/04/29 16:37:50 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpbrk(const char *s, const char *charset)
{
	const char	*c;

	if (!s || !charset)
		return (NULL);
	while (*s)
	{
		c = charset;
		while (*c)
		{
			if (*s == *c)
				return ((char *)s);
			c++;
		}
		s++;
	}
	return (NULL);
}
/**
 * Breaks a string into tokens based on a specified delimiter.
 *
 * @param str The string to be tokenized.
 * @param delimiter The delimiter used to split the string into tokens.
 * @return A pointer to an array of strings representing the tokens.
 */