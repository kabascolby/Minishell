/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 16:01:21 by lkaba             #+#    #+#             */
/*   Updated: 2019/03/05 01:49:36 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEQUE_H
# define FT_DEQUE_H
# include "libft.h"
# define U32 4294967295

typedef struct	s_deque
{
	void			*tab;
	uint32_t		front;
	uint32_t		rear;
	uint32_t		curr_size;
	uint32_t		max;
	uint32_t		data_size;
	uint32_t		capacity;
	uint32_t		f;
}				t_deque;

t_deque			init_deque(uint32_t length, uint8_t data_t_size);
uint8_t			ft_dq_grow(t_deque *dq);
void			enqueue_rear(t_deque *dq, void *data);
void			enqueue_front(t_deque *dq, void *data);
void			*dequeue_rear(t_deque *dq);
void			*dequeue_front(t_deque *dq);
uint8_t			is_dq_empty(t_deque *dq);
void			*dq_peek_rear(t_deque *dq);
void			*dq_peek_front(t_deque *dq);
void			*dq_arraydup(t_deque *dq);
#endif
