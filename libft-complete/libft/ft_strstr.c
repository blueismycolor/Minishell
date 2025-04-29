/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:28:42 by tlair             #+#    #+#             */
/*   Updated: 2025/04/29 17:03:19 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	size_t	needle_len;

	if (!haystack || !needle)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	i = 0;
	while (haystack[i] && i <= ft_strlen(haystack) - needle_len)
	{
		j = 0;
		while (needle[j] && haystack[i + j] == needle[j])
			j++;
		if (j == needle_len)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int main() {
	const char *haystack = "Hello, world!";
	const char *needle = "world";
	char *result = ft_strstr(haystack, needle);
	if (result) {
		printf("Needle found at index: %ld\n", result - haystack);
	} else {
		printf("Needle not found\n");
	}
	return 0;
}
*/