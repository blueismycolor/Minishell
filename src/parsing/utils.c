/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egatien <egatien@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:08:16 by egatien           #+#    #+#             */
/*   Updated: 2025/05/07 13:16:37 by egatien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	fonction ou le but est de recuperer la valeur de sortie de la
	derniere commande (utile pour '$?')
	en gros a chaque appel on peut recuperer la valeur de sortie de la commande
*/
int	last_exit_status(int exit_status)
{
	static int	status_to_return;

	if (exit_status != -1)
		status_to_return = exit_status;
	return (status_to_return);
}

char	*ft_tabstrnstr(const char *str, const char *to_find)
{
	size_t		name_len;
	size_t		to_find_len;
	const char	*equal_ptr;

	if (!str || !to_find)
		return (NULL);
	equal_ptr = ft_strchr(str, '=');
	if (!equal_ptr)
		return (NULL);
	name_len = equal_ptr - str;
	to_find_len = ft_strlen(to_find);
	if (name_len != to_find_len)
		return (NULL);
	if (ft_strncmp(str, to_find, name_len) == 0)
		return ((char *)str);
	return (NULL);
}

char	*set_env(char *str, char **envp)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != '$')
		i++;
	if (str[i] == '\0')
		return (ft_strdup(str));
	str = ft_strdup(str);
	return (put_env(str, envp));
}
