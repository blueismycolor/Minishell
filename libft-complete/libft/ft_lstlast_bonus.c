/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:54:47 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:54:49 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp -> next)
		tmp = tmp -> next;
	return (tmp);
}

/*int	main(void) 
{
    t_list *head = malloc(sizeof(t_list));
    t_list *second = malloc(sizeof(t_list));
    t_list *third = malloc(sizeof(t_list));

    head->content = "firstnode";
    head->next = second; 

    second->content = "secondnode";
    second->next = third;

    third->content = "thirdnode";
    third->next = NULL;

    t_list *last = ft_lstlast(head);

    if (last != NULL) {
        printf("the last node content: %s\n", (char *)last->content);
    } else {
        printf("empty list.\n");
    }
    free(third);
    free(second);
    free(head);

    return 0;
}*/