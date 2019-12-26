/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtable_resize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:19:11 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 20:50:54 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

uint64_t		get_hashidx(void *key, uint64_t buckets)
{
	return (ft_hash(key, ft_strlen(key)) % buckets);
}

static int8_t	hashtable_rehash_entry(t_hashtable **dest, t_entry **entry)
{
	uint32_t	index;

	if (dest && *dest && entry && *entry)
	{
		index = get_hashidx((*entry)->key, (*dest)->num_buckets);
		(*entry)->next = ((*dest)->buckets)[index];
		((*dest)->buckets)[index] = (*entry);
		(*dest)->entries += 1;
		return (1);
	}
	return (-1);
}

static int8_t	hashtable_rehash_table(t_hashtable **src, t_hashtable **dest)
{
	t_entry		*cur_entry;
	t_entry		*temp;
	uint32_t	i;

	if (src && *src && dest && *dest)
	{
		i = -1;
		while (++i < (*src)->num_buckets)
			if (((*src)->buckets)[i])
			{
				cur_entry = ((*src)->buckets)[i];
				while (cur_entry)
				{
					temp = cur_entry->next;
					if ((hashtable_rehash_entry(dest, &cur_entry) == -1))
						return (-1);
					cur_entry = temp;
				}
				((*src)->buckets)[i] = NULL;
			}
	}
	return (((*dest)->entries == (*src)->entries) ? 1 : -1);
}

int8_t			hashtable_grow(t_hashtable **table)
{
	t_hashtable	*new_table;

	if (table && *table)
	{
		if ((new_table = hashtable_init((*table)->num_buckets *
			HTAB_MULTIPLIER)))
		{
			if (hashtable_rehash_table(table, &new_table))
			{
				if (hashtable_destroy(table))
				{
					(*table) = new_table;
					return (1);
				}
			}
		}
	}
	return (-1);
}

int8_t			hashtable_shrink(t_hashtable **table)
{
	t_hashtable	*new_table;

	if (table && *table)
	{
		if ((*table)->num_buckets > 1)
		{
			new_table = hashtable_init((*table)->num_buckets / 2);
			if (new_table == NULL)
				return (-1);
			if (hashtable_rehash_table(table, &new_table))
			{
				if (hashtable_destroy(table))
				{
					(*table) = new_table;
					return (1);
				}
			}
		}
	}
	return (-1);
}
