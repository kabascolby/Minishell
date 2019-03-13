#include "hashtable.h"

t_hashtable		*hashtab_grow(t_hashtable *table)
{
	t_hashtable		*new_table;

	if (table)
	{
		new_table = hashtab_new((*table)->num_buckets * HTAB_MULTIPLIER);
		if (new_table)
		{
			if (hashtab_rehash_table(table, &new_table) == 0)
			{
				hashtab_destroy(table);
				(*table) = new_table;
				return (0);
			}
		}
	}
	return (-1);
}