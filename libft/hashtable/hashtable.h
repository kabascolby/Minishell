#ifndef HASHTABLE_H
# define HASHTABLE_H
# include "../libft.h"


# define HASHCODE(key, buckets) (ft_hash(key) % buckets)

# define INIT_HASHTABLE_SIZE 256
# define MIN_LOAD_FACTOR 0.0
# define MAX_LOAD_FACTOR 0.7
# define SIZETABLE 100

typedef struct s_entry		t_entry;
typedef struct	s_hashtable	t_hashtable;

struct		s_entry
{
	char			*key;
	void			*item;
	struct s_entry	*next;
};

struct		s_hashtable
{
	unsigned int	entries;
	unsigned int	num_buckets;
	t_entry			**bucket_list;
	void			(*create_table)(void (*))

};

void			*hashtable_init(void);
void			*hashtab_grow_table(void *);
void			*hashtab_shrink_table(void *);
void			*hashtab_fetch_entry(void *table, char *key);
void			*hashtab_insert_entry(void *table, char *key, void *item);
void			*hashtab_delete_entry(void *table, char *key);
void			*hashtab_rehash_entry(void *entry);
void			*hashtab_rehash_table(void *table_from,t_hashtable **table_to);
void			*hashtab_destroy_table(void *table);
void			*hashtab_set_appropriate_load_factor(void *table);
#endif
