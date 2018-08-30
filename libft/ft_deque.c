/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 21:19:22 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/31 14:16:51 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**############DMCA(by lkaba)#############################################
**This is an  amazing thing I'm making I called it the dynamic multitype
**circular array,  he can hold  any type even itself what is awesome.
**He can increase it own size, add  and remove items from
**the front and front the rear;
**Another amazing thing it's circulare Incredible Alhamdullah;
**with this array I can Implement a stack, or a queue or a  deque
**I can put a queue Inside the stack vice versa; And its faster because
**the data is store in a contigius block of memory
**the stucture of the algorithm it's self Is a perfection because it's
**It' based on mathematics formula.
**"s" : is the input data size Ex: size of "int" or "char *"
**"max": is the maximun size of the array
*/

uint8_t		dq_grow(t_deque *dq)
{
	uint8_t		*ptr;
	uint32_t	rear_index;
	uint32_t	old_rear;

	dq->capacity *= 2;
	dq->max *= 2;
	if (!(ptr = (void *)malloc(dq->capacity)))
		return (0);
	ft_memset((uint8_t *)ptr, 0, dq->capacity);
	old_rear = dq->rear * dq->data_size;
	rear_index = (dq->max * dq->data_size) -
	(((dq->max / 2) * dq->data_size) - old_rear);
	ft_memcpy(ptr + rear_index, (uint8_t *)dq->tab + old_rear,
		(dq->max * dq->data_size) - rear_index);
	ft_memcpy(ptr, dq->tab, dq->front * dq->data_size);
	dq->rear = rear_index / dq->data_size;
	free(dq->tab);
	dq->tab = (void *)ptr;
	return (1);
}

/*
**push_rear
*/

void		enqueue_rear(t_deque *dq, void *data)
{
	if (dq->curr_size == dq->max)
	{
		if (!dq_grow(dq))
			return ;
	}
	dq->rear -= 1;
	dq->rear %= dq->max;
	ft_memcpy(((uint8_t *)dq->tab) + dq->rear *
		dq->data_size, data, dq->data_size);
	dq->curr_size++;
}

/*
**push_front
*/

void		enqueue_front(t_deque *dq, void *data)
{
	if (dq->curr_size == dq->max)
	{
		if (!dq_grow(dq))
			return ;
	}
	ft_memcpy(((uint8_t *)dq->tab) + dq->front *
		dq->data_size, data, dq->data_size);
	dq->front = (dq->front + 1) % dq->max;
	dq->curr_size++;
}

/*
**pop_rear
*/

void		*dequeue_rear(t_deque *dq)
{
	void	*tmp;

	if (is_dq_empty(dq))
		return (NULL);
	tmp = (void *)malloc(dq->data_size);
	if (!tmp)
		return (NULL);
	ft_memcpy(tmp, ((uint8_t *)dq->tab) + dq->rear *
		dq->data_size, dq->data_size);
	dq->rear = (dq->rear + 1) % dq->max;
	dq->curr_size--;
	return (tmp);
}

/*
**pop from the front
*/

void		*dequeue_front(t_deque *dq)
{
	void	*tmp;

	if (is_dq_empty(dq))
		return (NULL);
	dq->front -= 1;
	dq->front %= dq->max;
	tmp = (void *)malloc(dq->data_size);
	if (!tmp)
		return (NULL);
	ft_memcpy(tmp, ((uint8_t *)dq->tab) + dq->front *
		dq->data_size, dq->data_size);
	dq->curr_size--;
	return (tmp);
}
