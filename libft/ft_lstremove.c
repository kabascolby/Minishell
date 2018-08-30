/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:12:07 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/05 19:05:17 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*list_remove(t_list *lst, void *ptr)
{
	t_list *temp;

	if (!lst)
		return (NULL);
	if (lst->content == ptr)
	{
		temp = lst->next;
		ft_memdel((void **)&lst);
		return (temp);
	}
	lst->next = list_remove(lst->next, ptr);
	return (lst);
}

/*
** Removes a single node from a linked list.
*/

void			ft_lstremove(t_list **lst, void *ptr)
{
	*lst = list_remove(*lst, ptr);
}
