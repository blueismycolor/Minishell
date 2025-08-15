/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:53:56 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:53:58 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	int		i;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		tmp = tmp ->next;
		i++;
	}
	return (i);
}

/*int	main(void)
{
	t_list	node1;
	t_list	node2;
	t_list	node3;
	t_list	*list;
	
	node1.content = "node1";
	node1.next = &node2;
	node2.content = "node2";
	node2.next = &node3;
	node3.content = "node3";
	node3.next = NULL;
	list = &node1;
	printf("sizeofthelist: %d\n", ft_lstsize(list));
	return (0);
}*/