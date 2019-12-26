/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_part2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 16:07:20 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 12:02:47 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_str.h"

char		dstr_get(t_dstr *dstr, uint32_t index)
{
	if (index < dstr->total)
		return (dstr->buff[index]);
	return ('\0');
}

void		dstr_set(t_dstr *dstr, uint32_t index, char c)
{
	if (index < dstr->total)
		dstr->buff[index] = c;
}

void		dstr_free(t_dstr *dstr)
{
	FREE(dstr->buff);
}

uint32_t	dstr_total(t_dstr *dstr)
{
	return (dstr->total);
}

void		dstr_init(t_dstr *dstr)
{
	dstr->buff = MALLOC(DYNAMIC_STR_CAPACITY);
	dstr->capacity = DYNAMIC_STR_CAPACITY;
	dstr->total = 0;
	dstr->dstr_total = dstr_total;
	dstr->dstr_add = dstr_add;
	dstr->dstr_set = dstr_set;
	dstr->dstr_get = dstr_get;
	dstr->dstr_delete = dstr_delete;
}
