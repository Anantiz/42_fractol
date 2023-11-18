/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:39:35 by aurban            #+#    #+#             */
/*   Updated: 2023/10/26 15:55:41 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_node;
	t_list	*del_node;

	if (!lst || !del)
		return ;
	del_node = *lst;
	while (del_node)
	{
		next_node = del_node->next;
		del(del_node->content);
		free(del_node);
		del_node = next_node;
	}
	*lst = NULL;
}
