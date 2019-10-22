/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:55:30 by lkaba             #+#    #+#             */
/*   Updated: 2019/10/17 23:57:41 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Creation a strong hash function this code will be improved in
*/

#include "hashtable.h"

uint64_t	ft_hash(void *key, uint64_t length)
{
	unsigned char	*p;
	uint64_t		h;
	uint64_t		i;

	h = 2166136261UL;
	p = (unsigned char *)key;
	i = -1;
	while (++i < length)
		h = (h * 16777619) ^ p[i];
	return (h);
}
