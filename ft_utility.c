/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 10:14:14 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/20 21:57:47 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**get_table(t_hashtable *ht)
{
	char		**tab;
	uint32_t	i;
	uint32_t	j;
	uint32_t	b;
	t_entry		*tmp;

	tab = (char **)malloc(sizeof(char *) * (ht->entries + 1));
	i = -1;
	j = -1;
	b = ht->num_buckets;
	while (++i < b)
	{
		if (ht->buckets[i])
		{
			tmp = ht->buckets[i];
			while (tmp)
			{
				tab[++j] = ft_join_args("", tmp->key, "=", tmp->item, NULL);
				tmp = tmp->next;
			}
			tab[j + 1] = NULL;
		}
	}
	return (tab);
}

t_vector	*hastable_keys(t_hashtable *ht, t_vector **keys)
{
	uint32_t	i;
	uint32_t	num;

	*keys = MALLOC(sizeof(t_vector));
	vector_init(*keys);
	i = -1;
	num = ht->num_buckets;
	while (++i < num)
		if (ht->buckets[i])
			vector_add(*keys, ht->buckets[i]->key);
	return (*keys);
}

int8_t		get_index(char *cmd, char *builtins)
{
	uint8_t	i;
	char	*tmp;

	i = 0;
	while ((tmp = ft_strtok_r(builtins, " ", &builtins)))
	{
		if (cmd && !ft_strcmp(cmd, tmp))
			break ;
		i++;
	}
	return (tmp ? i : -1);
}

/*
**disable canonical mode (buffered i/o) and local echo
**set the new settings immediately
*/

void		set_unbeffered(void)
{
	t_termios new_term_attr;

	tcgetattr(1, &new_term_attr);
	new_term_attr.c_lflag &= (~ICANON & ~ECHO);
	new_term_attr.c_cc[VMIN] = 0;
	new_term_attr.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term_attr);
}

/*
**restore terminal to canonical mode
*/

void		restor_terminal(t_shell *s)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &s->old_t_attr);
}
