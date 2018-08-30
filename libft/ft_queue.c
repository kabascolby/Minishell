/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 17:23:13 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/31 14:16:15 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**queue Init
*/

t_queue	*init(void)
{
	t_queue	*q;

	q = (t_queue *)malloc(sizeof(t_queue));
	q->front = NULL;
	q->rear = NULL;
	return (q);
}

/*
**Enqueue
*/

void	enqueue(t_queue *q, void *n)
{
	t_node	*tmp;

	tmp = (t_node *)malloc(sizeof(t_node));
	tmp->data = n;
	tmp->next = NULL;
	if (is_empty(q))
	{
		q->rear = tmp;
		q->front = tmp;
		return ;
	}
	q->rear->next = tmp;
	q->rear = tmp;
}

/*
**Dequeue
*/

void	*dequeue(t_queue *q)
{
	t_node	*tmp;
	void	*tp_data;

	tmp = q->front;
	if (is_empty(q))
		return (NULL);
	if (q->front == q->rear)
	{
		q->front = NULL;
		q->rear = NULL;
	}
	else
		q->front = q->front->next;
	tp_data = tmp->data;
	free(tmp);
	return (tp_data);
}

/*
**Give the value at the queue front
**front
*/

void	*peek(t_queue *q)
{
	return (q->front ? q->front->data : NULL);
}

/*
**Is_empty
*/

int		is_empty(t_queue *q)
{
	return (q->front == NULL);
}
