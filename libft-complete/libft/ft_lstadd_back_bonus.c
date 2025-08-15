/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:55:57 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:55:59 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = ft_lstlast(*lst);
	if (last)
		last->next = new;
	else
		*lst = new;
}

/*int	main(void)
{
    t_list *head = NULL;

    t_list *new_node1 = malloc(sizeof(t_list));
    t_list *new_node2 = malloc(sizeof(t_list));
    t_list *new_node3 = malloc(sizeof(t_list));

    if (!new_node1 || !new_node2 || !new_node3) 
    {
        	return 1;
    }

    new_node1->content = "firstnode";
    new_node1->next = NULL;

    new_node2->content = "secondnode";
    new_node2->next = NULL;

    new_node3->content = "thirdnode";
    new_node3->next = NULL;

    ft_lstadd_back(&head, new_node1);
    ft_lstadd_back(&head, new_node2);
    ft_lstadd_back(&head, new_node3);

    t_list *current = head;
    while (current) 
	{
        printf("the node content: %s\n", (char *)current->content);
        current = current->next;
	}
	return 0;
}*/