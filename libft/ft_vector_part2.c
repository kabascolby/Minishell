/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_part2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 10:38:23 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/20 18:40:17 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	*vector_get(t_vector *v, int index)
{
	if (index >= 0 && index < v->total)
		return (v->items[index]);
	return (NULL);
}

void	vector_set(t_vector *v, int index, void *item)
{
	if (index >= 0 && index < v->total)
		v->items[index] = item;
}

void	vector_free(t_vector **v)
{
	if (*v && (*v)->items)
		free((*v)->items);
	**v = (t_vector){0, 0, 0, 0, 0, 0, 0, 0};
	free(*v);
	*v = NULL;
}

int		vector_total(t_vector *v)
{
	return (v->total);
}
