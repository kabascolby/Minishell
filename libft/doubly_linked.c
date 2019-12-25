/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 11:49:09 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/24 11:01:34 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**Create a double linked list node
*/

t_dllnode	*create_dllnode(void *data)
{
	t_dllnode	*temp;

	temp = (t_dllnode *)malloc(sizeof(t_dllnode));
	temp->data = data;
	temp->prev = NULL;
	temp->next = NULL;
	return (temp);
}

/*
** Insert a node at the head of given linked list
** first time the head is NULL so the
** the temp->next will be NULL at the first time;
** We can call this operation Push or Insert at head
*/

void		pushdll(void *data, t_dllnode **head)
{
	t_dllnode	*temp;

	temp = create_dllnode(data);
	if (!*head)
		*head = temp;
	(*head)->prev = temp;
	temp->next = *head;
	*head = temp;
}

/*
** Check if the position exist to avoid leaks
*/

int			is_ddl_overflow(size_t pos, t_dllnode *head)
{
	t_dllnode	*tmp;
	size_t		i;

	tmp = head;
	i = 0;
	while (tmp && ++i)
		tmp = tmp->next;
	if (pos > i + 1)
	{
		ft_putendl("Position overflow");
		return (1);
	}
	return (0);
}

/*
** Ad a node at any given position whe have to know
** the number of node;
** We Insert the node at the given position
*/

void		insertddl(size_t pos, void *data, t_dllnode **head)
{
	t_dllnode	*temp;
	t_dllnode	*temp2;
	size_t		i;

	if (is_ddl_overflow(pos, *head))
		return ;
	temp = create_dllnode(data);
	if (pos == 1)
	{
		pushdll(data, head);
		return ;
	}
	temp2 = *head;
	i = -1;
	while (++i < pos - 1)
		temp2 = temp2->next;
	temp->next = temp2->next;
	temp2->next = temp;
	temp->prev = temp2;
	temp->next->prev = temp;
}

/*
**Reverse a linked list
**Before changing head, check for the cases like empty
**list and list with only one node
*/

void		reverseddl(t_dllnode *head)
{
	t_dllnode	*temp;
	t_dllnode	*current;

	temp = NULL;
	current = head;
	while (current)
	{
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = current->prev;
	}
	if (temp)
		head = temp->prev;
}
