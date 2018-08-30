/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 03:43:28 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/10 06:18:02 by lkaba            ###   ########.fr       */
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

t_deque		init_deque(uint32_t length, uint8_t data_t_size)
{
	t_deque	dq;

	dq.rear = 0;
	dq.front = 0;
	dq.f = 0;
	dq.curr_size = 0;
	dq.max = length;
	dq.data_size = data_t_size;
	dq.capacity = length * data_t_size;
	dq.tab = malloc(dq.capacity);
	return (dq);
}

uint8_t		is_dq_empty(t_deque *dq)
{
	return (dq->curr_size == 0);
}

/*
**rear
*/

void		*dq_peek_rear(t_deque *dq)
{
	return (dq->tab + dq->rear * dq->data_size);
}

/*
**front
*/

void		*dq_peek_front(t_deque *dq)
{
	return (dq->tab + (dq->front == 0 ?
		(dq->max - 1) : (dq->front - 1)) * dq->data_size);
}

/*
**	Returns a copy of the circular array, converted to a linear array
*/

void		*dq_arraydup(t_deque *dq)
{
	void		*tmp;

	if (is_dq_empty(dq))
		return (NULL);
	tmp = malloc(dq->data_size * dq->curr_size);
	if (!tmp)
		return (NULL);
	if (dq->rear < dq->front)
	{
		ft_memcpy(tmp, dq->tab + (dq->rear * dq->data_size),
			(dq->front - dq->rear) * dq->data_size);
	}
	else
	{
		ft_memcpy(tmp, dq->tab + (dq->rear * dq->data_size),
			(dq->max - dq->rear) * dq->data_size);
		ft_memcpy(tmp + ((dq->max - dq->rear) * dq->data_size),
			dq->tab, dq->front * dq->data_size);
	}
	return (tmp);
}
