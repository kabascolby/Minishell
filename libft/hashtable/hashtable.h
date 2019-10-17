/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 19:37:47 by lkaba             #+#    #+#             */
/*   Updated: 2019/10/16 20:31:17 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "../libft.h"
#define HTAB_MULTIPLIER 2
#define HTAB_DIVISER 2
#define HASHCODE(key, buckets) (ft_hash(key, ft_strlen(key)) % buckets)

#define INIT_HASHTABLE_SIZE 257
#define MIN_LOAD_FACTOR 0.0
#define MAX_LOAD_FACTOR 0.7
#define NUMBUCKET 100

typedef struct s_entry t_entry;
typedef struct s_hashtable t_hashtable;

struct s_entry
{
	char *key;
	void *item;
	struct s_entry *next;
};

struct s_hashtable
{
	uint64_t entries;
	uint64_t num_buckets;
	t_entry **buckets;
	t_hashtable *(*insert)(t_hashtable *, char *, void *);
};

t_hashtable *hashtable_init(uint32_t len);
uint64_t hash(void *key, uint64_t length);
uint32_t hashtable_insert(t_hashtable **table, void *key, void *item);
uint8_t hashtable_rehash_table(t_hashtable **src, t_hashtable **dest);
int hashtab_grow(t_hashtable **table);
#endif
