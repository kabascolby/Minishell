#ifndef HASHTABLE_H
# define HASHTABLE_H
# include "../libft.h"
# define HASHCODE(key, buckets) (ft_hash(key) % buckets)

# define INIT_HASHTABLE_SIZE 256

# define MIN_LOAD_FACTOR 0.0
# define MAX_LOAD_FACTOR 0.7

# define HTAB_MULTIPLIER 2
# define HTAB_DIVISER 2

# define HASHCODE(key, buckets) (ft_hash(key) % buckets)

# define INIT_HASHTABLE_SIZE 256
# define MIN_LOAD_FACTOR 0.0
# define MAX_LOAD_FACTOR 0.7
# define NUMBUCKET 100

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
	t_entry			**buckets;
	void			*(*new_hashtable)(void *);

};

void			*hashtable_init(void);
t_hashtable		*hashtab_insert(t_hashtable *table, char *key, void *item);
t_hashtable		*hashtab_grow(t_hashtable *table);

#endif
