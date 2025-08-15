/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extend_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:33:48 by tlair             #+#    #+#             */
/*   Updated: 2025/05/12 15:34:05 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_extend_array(char **array, const char *new_str)
{
	int		i;
	int		j;
	char	**new_array;

	i = 0;
	j = -1;
	while (array && array[i])
		i++;
	new_array = malloc(sizeof(char *) * (i + 2));
	if (!new_array)
		return (NULL);
	while (++j < i)
		new_array[j] = array[j];
	new_array[j] = ft_strdup(new_str);
	if (!new_array[j])
	{
		free(new_array);
		return (NULL);
	}
	new_array[j + 1] = NULL;
	free(array);
	return (new_array);
}
