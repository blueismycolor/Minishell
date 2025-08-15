/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:31:03 by tlair             #+#    #+#             */
/*   Updated: 2025/05/12 15:48:42 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*save;
	char		*token;
	char		*end;

	if (str)
		save = str;
	if (!save || !*save)
		return (NULL);
	token = save;
	end = ft_strpbrk(save, delim);
	if (end)
	{
		*end = '\0';
		save = end + 1;
	}
	else
		save = NULL;
	return (token);
}
/**
 * Splits a string into tokens based on a delimiter.
 *
 * @param str The string to be tokenized.
 * @param delim The delimiter used to split the string.
 * @return A pointer to the first token found in the string,
 * or NULL if no token is found.
 */