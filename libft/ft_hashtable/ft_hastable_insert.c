/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hastable_insert.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 08:56:36 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 20:50:54 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

static t_entry	*new_entry(void *key, void *item)
{
	t_entry		*new_entry;

	if (key && item)
	{
		if (!(new_entry = (t_entry *)malloc(sizeof(t_entry))))
			return (NULL);
		new_entry->key = key;
		new_entry->item = item;
		new_entry->next = NULL;
		return (new_entry);
	}
	return (NULL);
}

static int8_t	set_load_factor(t_hashtable **table)
{
	if (table && *table)
	{
		if ((float)(*table)->entries /
			(float)(*table)->num_buckets > MAX_LOAD_FACTOR)
			return (hashtable_grow(table));
		if ((float)(*table)->entries /
			(float)(*table)->num_buckets < MIN_LOAD_FACTOR)
			return (hashtable_shrink(table));
		return (0);
	}
	return (-1);
}

int32_t			hashtable_insert(t_hashtable **table, void *key, void *item)
{
	t_entry		*entry;
	uint32_t	index;

	if (table && key && item)
	{
		if ((*table) == NULL)
			(*table) = hashtable_init(INIT_HASHTABLE_SIZE);
		if (*table && (set_load_factor(table) != -1))
		{
			if (!(entry = new_entry(key, item)))
				return (-1);
			index = get_hashidx(key, (*table)->num_buckets);
			entry->next = ((*table)->buckets)[index];
			((*table)->buckets)[index] = entry;
			(*table)->entries += 1;
			return (index);
		}
	}
	return (-1);
}

int8_t			hashtable_update(t_hashtable **table, void *key, void *item)
{
	t_entry *entry;

	if ((entry = hashtable_get_entry(*table, key)))
	{
		free(entry->item);
		entry->item = item;
		return (1);
	}
	return (-1);
}
