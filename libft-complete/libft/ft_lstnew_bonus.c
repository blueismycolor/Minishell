/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:54:07 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:54:09 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}

/*void	print_list(t_list *list)
{
	while (list != NULL)
	{
		printf ("%d ->", *(int *)list->content);
		list = list ->next;
	}
}

int	main(void)
{
    int value = 42;
    t_list *node = ft_lstnew(&value);

    if (node != NULL)
    {
        printf("Düğüm içeriği: %d\n", *(int *)node->content);
        print_list(node);
    }	
	free(node);
	return 0;
}*/