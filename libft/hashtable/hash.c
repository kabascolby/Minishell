/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:55:30 by lkaba             #+#    #+#             */
/*   Updated: 2019/10/16 12:19:39 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Creation a strong hash function this code will be improved in
**
**
**
**
**
*/

#include "hashtable.h"

uint64_t hash(void *key, uint64_t length)
{
	unsigned char *p = (unsigned char *)key;
	uint64_t h = 2166136261UL;
	uint64_t i;

	i = -1;
	while (++i < length)
		h = (h * 16777619) ^ p[i];
	return h;
}
