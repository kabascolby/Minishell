/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memtrack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:01:34 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/21 20:17:40 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memtrack.h"

static t_memtrack *mem_init(uint64_t size)
{
	t_memtrack *mt;
	uint64_t len;

	mt = MALLOC(sizeof(t_memtrack));
	mt->size = size ? size : MEMSIZE;
	mt->count = -1;
	mt->membuff = MALLOC(sizeof(void *) * mt->size);
	return (mt);
}

void *ft_mtnew(t_memtrack **mt, void *ptr)
{
	void **tmp;

	if (!*mt)
		*mt = mem_init(0);

	(*mt)->membuff[++(*mt)->count] = ptr;
	if ((*mt)->count + 1 >= (*mt)->size)
	{
		tmp = malloc(((*mt)->size + MEMSIZE) * sizeof(void *));
		memcpy((void **)tmp, (void **)(*mt)->membuff, (*mt)->size * sizeof(void *));
		(*mt)->size += MEMSIZE;
		FREE((*mt)->membuff);
		(*mt)->membuff = tmp;
		tmp = NULL;
	}
	return (*mt)->membuff[(*mt)->count];
}
