/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 19:37:47 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/26 09:35:13 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H
# include "../libft.h"
# define HTAB_MULTIPLIER 2
# define HTAB_DIVISER 2
# define INIT_HASHTABLE_SIZE 257
# define MIN_LOAD_FACTOR 0.0
# define MAX_LOAD_FACTOR 0.7
# define NUMBUCKET 100

typedef struct s_entry		t_entry;
typedef struct s_hashtable	t_hashtable;
struct						s_entry
{
	char			*key;
	void			*item;
	struct s_entry	*next;
};

struct						s_hashtable
{
	uint64_t	entries;
	uint64_t	num_buckets;
	t_entry		**buckets;
	int32_t		(*insert)(t_hashtable **, void *, void *);
	int8_t		(*update)(t_hashtable **, void *, void *);
	int8_t		(*destroy)(t_hashtable **);
	t_entry		*(*get_entry)(t_hashtable *, void *);
	void		*(*pop_item)(t_hashtable **, void *);
	uint32_t	(*count_entry)(t_hashtable *);
};

t_hashtable					*hashtable_init(uint32_t len);
uint64_t					ft_hash(void *key, uint64_t length);
int32_t						hashtable_insert(t_hashtable **table,
								void *key, void *item);
int8_t						hashtable_update(t_hashtable **table,
								void *key, void *item);
t_entry						*hashtable_get_entry(t_hashtable *table, void *key);
int8_t						hashtable_destroy(t_hashtable **table);
int8_t						hashtable_grow(t_hashtable **table);
int8_t						hashtable_shrink(t_hashtable **table);
void						free_entry(t_entry **entry);
void						*hashtable_popitem(t_hashtable **table, void *key);
uint32_t					hashtable_count_entries(t_hashtable *table);
uint64_t					get_hashidx(void *key, uint64_t buckets);
#endif
