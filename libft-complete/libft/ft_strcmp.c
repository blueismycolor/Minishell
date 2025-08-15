/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:26:41 by tlair             #+#    #+#             */
/*   Updated: 2025/04/29 16:27:40 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	if (!s1 || !s2)
		return (-1);
	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	while (*p1 && *p1 == *p2)
	{
		p1++;
		p2++;
	}
	return (*p1 - *p2);
}

/*
#include <stdio.h>

int main() {
	const char *s1 = "Hello";
	const char *s2 = "World";
	int result = ft_strcmp(s1, s2);
	printf("Comparison result: %d\n", result);
	return 0;
}
*/