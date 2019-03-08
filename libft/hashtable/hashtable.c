#include "hashtable.h"


void		*hashtable_init(void)
{
	t_hashtable		*table;
	uint16_t		i;
	uint16_t		size;

	size = SIZETABLE;
	if (size < 1)
		return (NULL);
	if (!(table = (t_hashtable *)malloc(sizeof(t_hashtable))))
		return (NULL);
	size = (unsigned int)ft_find_next_prime(size);
	if (!(table->bucket_list =
			malloc(sizeof(t_entry*) * size)))
	{
		free(table);
		return (NULL);
	}
	table->num_buckets = size;
	table->entries = 0;
	i = 0;
	while (i < size)
		(table->bucket_list)[i++] = NULL;
	return (table);
}