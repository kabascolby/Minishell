/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtable_ini.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 19:23:28 by lkaba             #+#    #+#             */
/*   Updated: 2019/10/17 23:17:02 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

static void	init(t_hashtable **table)
{
	(*table)->insert = hashtable_insert;
	(*table)->destroy = hashtable_destroy;
	(*table)->get_entry = hashtable_get_entry;
	(*table)->pop_item = hashtable_popitem;
	(*table)->count_entry = hashtable_count_entries;
}

t_hashtable	*hashtable_init(uint32_t len)
{
	t_hashtable	*table;
	uint64_t	size;
	uint64_t	i;

	if (len < 1)
		return (NULL);
	if (!(table = (t_hashtable *)malloc(sizeof(t_hashtable))))
		return (NULL);
	size = ft_isprime(len) ? len : ft_find_next_prime(len);
	if (!(table->buckets = (t_entry **)malloc(sizeof(t_entry *) * size)))
	{
		free(table);
		return (NULL);
	}
	table->num_buckets = size;
	table->entries = 0;
	i = -1;
	while (size > ++i)
		(table->buckets)[i] = NULL;
	init(&table);
	return (table);
}
