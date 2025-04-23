/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:52:05 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:52:08 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static size_t	ft_wordcount(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != c) && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static void	ft_freeall(char **tableau, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(tableau[i]);
		i++;
	}
	free(tableau);
}

static int	ft_fillwords(char **tableau, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	word_len;

	i = 0;
	j = 0;
	while (s[j])
	{
		if (s[j] != c)
		{
			word_len = ft_wordlen(s + j, c);
			tableau[i] = malloc((word_len + 1) * sizeof(char));
			if (!tableau[i])
			{
				ft_freeall(tableau, i);
				return (0);
			}
			ft_strlcpy(tableau[i++], s + j, word_len + 1);
			j = j + ft_wordlen(s + j, c);
		}
		else
			j++;
	}
	return (1);
}

char	**ft_split(const char *s, char c)
{
	size_t		word_count;
	char		**tableau;

	word_count = ft_wordcount(s, c);
	tableau = malloc((word_count + 1) * sizeof(char *));
	if (!tableau)
		return (NULL);
	tableau[word_count] = NULL;
	if (!ft_fillwords(tableau, s, c))
		return (NULL);
	return (tableau);
}

/*int	main(void)
{
	char *tableau = "salut,comment,ca,va,?";
    	char sep = ',';
    	char **res = ft_split(tableau, sep);
    
    if (!res)
    {
        printf("Memory allocation failed.\n");
        return (1);
    }
    for (int i = 0; res[i]; i++)
    {
        printf("Word %d: %s\n", i, res[i]);
        free(res[i]);
    }

    free(res);
    return (0);
}*/