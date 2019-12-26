/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_part1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 18:49:03 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 12:02:47 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void		vector_init(t_vector *v)
{
	v->items = MALLOC(sizeof(void *) * VECTOR_INIT_CAPACITY);
	v->capacity = VECTOR_INIT_CAPACITY;
	v->total = 0;
	v->vector_total = vector_total;
	v->vector_add = vector_add;
	v->vector_set = vector_set;
	v->vector_get = vector_get;
	v->vector_delete = vector_delete;
}

static void	vector_resize(t_vector *v, int capacity)
{
	void **items;

	items = MALLOC(sizeof(void *) * capacity);
	if (items)
	{
		ft_memcpy((void **)items, (void **)v->items,
		sizeof(void *) * v->capacity);
		FREE(v->items);
		v->items = items;
		items = NULL;
		v->capacity = capacity;
	}
}

void		vector_add(t_vector *v, void *item)
{
	if (v->capacity == v->total)
		vector_resize(v, v->capacity + VECTOR_INIT_CAPACITY);
	v->items[v->total++] = item;
}

void		vector_delete(t_vector *v, int index)
{
	int i;

	if (index < 0 || index >= v->total)
		return ;
	v->items[index] = NULL;
	i = index;
	while (i < v->total - 1)
	{
		v->items[i] = v->items[i + 1];
		v->items[i + 1] = NULL;
		i++;
	}
	v->total--;
	if (v->total > 0 && v->total == v->capacity / 4)
		vector_resize(v, v->capacity / 2);
}
