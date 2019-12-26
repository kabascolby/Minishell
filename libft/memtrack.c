/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memtrack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:01:34 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 12:02:47 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memtrack.h"

t_memtrack	*memtracker_init(uint64_t size)
{
	t_memtrack	*mt;

	mt = MALLOC(sizeof(t_memtrack));
	mt->size = size ? size : MEMSIZE;
	mt->count = -1;
	mt->membuff = MALLOC(sizeof(void *) * mt->size);
	mt->track = ft_mtnew;
	mt->destroy = ft_mtdestroy;
	return (mt);
}

void		*ft_mtnew(t_memtrack **mt, void *ptr)
{
	void		**tmp;
	uint64_t	i;

	if (!*mt)
		*mt = memtracker_init(0);
	if ((*mt)->count + 1 >= (*mt)->size)
	{
		i = -1;
		tmp = MALLOC(((*mt)->size + MEMSIZE) * sizeof(void *));
		while (++i < (*mt)->size)
			tmp[i] = (*mt)->membuff[i];
		(*mt)->size += MEMSIZE;
		FREE((*mt)->membuff);
		(*mt)->membuff = tmp;
		tmp = NULL;
	}
	(*mt)->membuff[++(*mt)->count] = ptr;
	return (*mt)->membuff[(*mt)->count];
}

void		ft_mtdestroy(t_memtrack *mt)
{
	int64_t	i;

	i = (int64_t)mt->size;
	while (--i >= 0)
	{
		if (mt->membuff[i] != NULL)
			FREE(mt->membuff[i]);
	}
	FREE(mt->membuff);
}
