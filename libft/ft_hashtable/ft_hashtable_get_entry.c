/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtable_get_entry.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 11:44:01 by lkaba             #+#    #+#             */
/*   Updated: 2019/10/17 12:54:33 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

t_entry	*hashtable_get_entry(t_hashtable *table, void *key)
{
	t_entry		*cur_entry;
	uint64_t	index;

	if (table && key)
	{
		index = HASHCODE(key, table->num_buckets);
		cur_entry = (table->buckets)[index];
		while (cur_entry)
		{
			if (ft_strcmp(cur_entry->key, key) == 0)
				return (cur_entry);
			cur_entry = cur_entry->next;
		}
	}
	return (NULL);
}
