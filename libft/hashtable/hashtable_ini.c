#include "hashtable.h"


void		*hashtable_init(void)
{
	t_hashtable		*table;
	uint16_t		i;
	uint16_t		size;

	if (size < 1)
		return (NULL);
	if (!(table = (t_hashtable *)malloc(sizeof(t_hashtable))))
		return (NULL);
	size = (unsigned int)ft_find_next_prime(NUMBUCKET);
	if (!(table->buckets =
			(t_entry **)malloc(sizeof(t_entry *) * size)))
	{
		free(table);
		return (NULL);
	}
	table->num_buckets = size;
	table->entries = 0;
	i = -1;
	while (size > ++i)
		table->buckets[i] = NULL;
	return (table);
}


t_entry		*new_entry(char *key, void *item)
{
	t_entry *new_entry;

	if (key && item)
	{
		if (!(new_entry = (t_entry *)malloc(sizeof(t_entry))))
			return (NULL);
		new_entry->key = ft_strdup(key);
		new_entry->item = item;
		new_entry->next = NULL;
		return (new_entry);
	}
	return (NULL);
}

int		ft_find_next_prime(int n)
{
	if (EVEN(n))
		n++;
	else
		n += 2;
	while (!ft_isprime(n))
		n += 2;
	return (n);
}