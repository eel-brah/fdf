/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:42:30 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/04 10:06:16 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;
	t_list	*ptr;

	if (!lst || !del)
		return ;
	node = *lst;
	while (node)
	{
		ptr = node;
		node = node->next;
		ft_lstdelone(ptr, del);
	}
	*lst = NULL;
}
