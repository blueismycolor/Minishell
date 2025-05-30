/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:51:33 by aeudes            #+#    #+#             */
/*   Updated: 2025/05/27 15:30:57 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char	*str)
{
	int		i;
	int		len_str;
	char	*new;

	if (!str)
		return (NULL);
	len_str = ft_strlen((char *)str);
	new = (char *)malloc(len_str * sizeof(char) + 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
/*int	main(void)
{
	char	str[] = "salut comment ca va";
	char	*result = ft_strdup(str);
	
	if(result != NULL)
		printf("%s\n", result);
	free(result);
	return (0);
}*/