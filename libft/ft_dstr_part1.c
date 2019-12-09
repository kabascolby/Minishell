/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_part1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 13:45:50 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/08 11:38:48 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_str.h"

static void	dstr_resize(t_dstr *dstr, uint32_t capacity)
{
	char	*tmp;

	tmp = MALLOC(sizeof(capacity));
	if (tmp)
	{
		ft_memcpy(tmp, dstr->buff, dstr->total);
		FREE(dstr->buff);
		dstr->buff = tmp;
		tmp = NULL;
		dstr->capacity = capacity;
	}
}

void		dstr_add(t_dstr *dstr, char c)
{
	if (dstr->capacity - 1 == dstr->total)
		dstr_resize(dstr, dstr->capacity + DYNAMIC_STR_CAPACITY);
	dstr->buff[dstr->total++] = c;
}

void		dstr_delete(t_dstr *dstr, uint32_t index)
{
	int	i;

	if (index > dstr->total)
		return ;
	dstr->buff[index] = '\0';
	i = index;
	ft_strcpy(&dstr->buff[i], &dstr->buff[i + 1]);
	dstr->total--;
	if (dstr->total > 0 && dstr->total == dstr->capacity / 4)
		dstr_resize(dstr, dstr->capacity / 2);
}

/*
**Join a string to the dynamic string at a given position
*/

void		dstr_join_str(t_dstr *dstr, char *str, uint32_t index)
{
	uint32_t	len;
	uint32_t	rem;
	char		*dest;

	if ((index > dstr->total) || !str || !*str)
		return ;
	len = ft_strlen(str);
	if (dstr->total + len >= dstr->capacity - 1)
		dstr_resize(dstr, dstr->capacity + DYNAMIC_STR_CAPACITY);
	rem = dstr->total - index;
	dest = dstr->buff + index;
	ft_memmove(dest + len, dest, rem);
	ft_memcpy(dest, str, len);
	dstr->total += len;
}

void		dstr_remove(t_dstr *dstr, uint32_t index, uint32_t size)
{
	uint32_t offset;

	offset = ft_strlen(dstr->buff) - index;
	ft_memmove(&dstr->buff[index], dstr->buff + index + size, offset);
	dstr->total -= size;
}
