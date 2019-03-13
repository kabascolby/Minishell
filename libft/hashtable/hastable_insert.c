#include "hashtable.h"

static t_hashtable	*hashtab_set_appropriate_load_factor(t_hashtable *table)
{
	if (table && *table)
	{
		if ((float)(*table)->entries / (float)(*table)->num_buckets
			> MAX_LOAD_FACTOR)
		{
			if (hashtab_grow(table) == -1)
				return (-1);
			return (0);
		}
		if ((float)(*table)->entries / (float)(*table)->num_buckets
			< MIN_LOAD_FACTOR)
		{
			if (hashtab_shrink(table) == -1)
				return (-1);
			return (0);
		}
		else
		{
			return (0);
		}
	}
	return (-1);
}


t_hashtable		*hashtab_insert(t_hashtable *table, char *key, void *item)
{
	t_entry			*entry;
	unsigned int	index;

	if (table && key && item)
	{
		if ((*table) == NULL)
			(*table) = hashtab_init();
		if (*table)
		{
			if (hashtab_set_appropriate_load_factor(table) == -1)
				return (-1);
			if (!(entry = new_entry(key, item)))
				return (-1);
			index = HASHCODE(key, (*table)->num_buckets);
			entry->next = ((*table)->buckets)[index];
			((*table)->buckets)[index] = entry;
			(*table)->entries += 1;
			return (index);
		}
	}
	return (-1);
}