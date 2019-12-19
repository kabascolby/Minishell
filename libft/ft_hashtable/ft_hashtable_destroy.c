/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtable_destroy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 09:06:57 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/11 15:55:01 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

void		free_entry(t_entry **entry)
{
	if (entry && *entry)
	{
		if ((*entry)->key)
			free((*entry)->key);
		if ((*entry)->item)
			free((*entry)->item);
		free(*entry);
		(*entry) = NULL;
	}
}

static void	free_bucket(t_entry **head)
{
	t_entry	*temp;

	if (head)
	{
		while (*head)
		{
			temp = (*head);
			(*head) = (*head)->next;
			free_entry(&temp);
		}
	}
}

int8_t		hashtable_destroy(t_hashtable **table)
{
	uint32_t	i;

	if (table && *table)
	{
		if ((*table)->buckets)
		{
			i = 0;
			while (i < (*table)->num_buckets)
			{
				if (((*table)->buckets)[i])
					free_bucket(&((*table)->buckets)[i]);
				i++;
			}
			free((*table)->buckets);
			(*table)->buckets = NULL;
		}
		free(*table);
		(*table) = NULL;
		return (1);
	}
	return (-1);
}
