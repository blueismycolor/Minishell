/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:55:45 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:55:47 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new -> next = *lst;
	*lst = new;
}

/*void	print_list(t_list *lst)
{
	while (lst)
	{
		printf ("%s -> ", (char *)lst -> content);
		lst = lst ->next;
	}
	printf ("NULL\n");
}*/

/*int	main(void)
{
    t_list *list = NULL;

    t_list node1;
    t_list node2;
    
    node1.content = "node1";
    node1.next = NULL;
    node2.content = "node2";
    node2.next = NULL;

    ft_lstadd_front(&list, &node1);
    printf("Listeye 'Dugum 1' eklendi:\n");
    print_list(list);

    ft_lstadd_front(&list, &node2);
    printf("\nListeye 'Dugum 2' eklendi:\n")
    print_list(list);
    return 0;
}*/