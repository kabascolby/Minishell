/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynamic_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 20:03:33 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/02 04:19:54 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dynamic_array		ft_init_dynamic_array(size_t length, size_t data_t_size)
{
	t_dynamic_array	da;

	ft_bzero(&da, sizeof(t_dynamic_array));
	if (!length)
	{
		ft_putendl("length is null");
		return (da);
	}
	da.length = 0;
	da.item_size = data_t_size;
	da.capacity = length * data_t_size;
	da.tab = (void *)malloc(da.capacity);
	ft_memset(da.tab, 0, da.capacity);
	return (da);
}

uint8_t				ft_darray_grow(t_dynamic_array *da)
{
	void	*ptr;
	size_t	cap;
	size_t	i;

	cap = da->capacity * 2;
	if (!(ptr = (void *)malloc(cap)))
		return (0);
	if (da->tab)
	{
		i = -1;
		while (++i < (da->capacity / da->item_size))
			ft_memcpy((((uint8_t *)ptr) + i * da->item_size),
				(((uint8_t *)da->tab) + i * da->item_size), da->item_size);
		ft_memset((((uint8_t *)ptr) + da->capacity), 0, (cap - da->capacity));
	}
	free(da->tab);
	da->tab = ptr;
	da->capacity = cap;
	return (1);
}

void				ft_add_to_darray(void *data, t_dynamic_array *da)
{
	if (da->length == da->capacity / da->item_size)
		if (!ft_darray_grow(da))
		{
			ft_putendl("ft_darray_grow operation fail");
			return ;
		}
	ft_memcpy(((uint8_t *)da->tab) + da->length *
		da->item_size, data, da->item_size);
	da->length += 1;
}
