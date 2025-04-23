/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:55:29 by aeudes            #+#    #+#             */
/*   Updated: 2025/02/09 11:55:32 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
	free(*lst);
	*lst = NULL;
}
/*void	del(void *content)
{
	free(content);
}

void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%s -> ", (char *)lst->content);
		lst = lst->next;
	}
	printf("NULL\n");
}
int main(void)
{
	t_list *lst = ft_lstnew(strdup("Node 1"));
	lst->next = ft_lstnew(strdup("Node 2"));
	lst->next->next = ft_lstnew(strdup("Node 3"));

	printf("Liste başlatıldı: ");
	print_list(lst);
	ft_lstclear(&lst, del);

	printf("Liste temizlendikten sonra: ");
	print_list(lst);
	return (0);
}*/