/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:48:43 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:48:46 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	s1_len;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	s1_len = ft_strlen(s1);
	while (ft_strchr(set, s1[i]))
		i++;
	while (ft_strchr(set, s1[s1_len - 1]))
		s1_len--;
	return (ft_substr(s1, i, s1_len - i));
}
/*int	main(void)
{
	char	str[] = "*hello world*";
	char	*set = "*";;
	char	*result = ft_strtrim(str,set);

	if (result)
		printf("%s\n", result);
	else
		printf("no info");
	free(result);
	return (0);
}*/