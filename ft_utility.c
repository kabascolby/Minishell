/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 10:14:14 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/28 19:02:59 by lkaba            ###   ########.fr       */
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

int8_t		get_index(t_shell *s, char *cmd, ...)
{
	uint8_t	i;
	va_list	args;

	va_start(args, cmd);
	i = 0;
	while (i < s->fptr_len)
	{
		if (SE_(va_arg(args, char *), cmd))
			break ;
		i++;
	}
	va_end(args);
	return (i ? i : -1);
}

/*
**disable canonical mode (buffered i/o) and local echo
**set the new settings immediately
*/

void		set_unbeffered(void)
{
	t_termios new_term_attr;

	tcgetattr(STDIN_FILENO, &new_term_attr);
	new_term_attr.c_lflag &= (~ICANON & ~ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term_attr);
	new_term_attr.c_cc[VMIN] = 1;
	new_term_attr.c_cc[VTIME] = 0;
}

void		reset_terminal(t_shell *s)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &s->old_t_attr);
}
