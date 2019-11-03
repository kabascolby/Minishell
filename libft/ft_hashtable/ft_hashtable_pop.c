/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtable_pop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 11:54:10 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/01 20:22:07 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

static void	*popitem_util(t_hashtable **table, t_entry *first_entry,
					unsigned int index, char *key)
{
	t_entry		*prev_entry;
	t_entry		*cur_entry;
	void		*item;

	cur_entry = first_entry;
	while (cur_entry)
	{
		if (ft_strcmp(cur_entry->key, key) == 0)
		{
			if (cur_entry == ((*table)->buckets)[index])
				((*table)->buckets)[index] = cur_entry->next;
			else
				prev_entry->next = cur_entry->next;
			item = cur_entry->item;
			(*table)->entries -= 1;
			free_entry(&cur_entry);
			return (item);
		}
		prev_entry = cur_entry;
		cur_entry = cur_entry->next;
	}
	return (NULL);
}

void		*hashtable_popitem(t_hashtable **table, void *key)
{
	uint64_t	index;

	if (table && *table && key)
	{
		index = HASHCODE(key, (*table)->num_buckets);
		return (
			popitem_util(table, ((*table)->buckets)[index], index, key));
	}
	return (NULL);
}
