/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:51:48 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:51:51 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *arr, int value)
{
	int	i;

	i = 0;
	while (arr[i] != (char)value && arr[i])
		i++;
	if (arr[i] == (char)value)
		return ((char *)arr + i);
	return (NULL);
}
/*int	main(void)
{
	char	arr[] = "salut comment ca va";
	char	value=  'u';
	char	*result = ft_strchr(arr, value);
	if (result != NULL)
		printf ("char '%c' found at position : %ld\n", value, result - arr);
	else
		printf ("char '%c' not found.\n", value);
	return (0);
}*/	