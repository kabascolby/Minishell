/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sp_char_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:25:14 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/10 20:55:20 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hash_handler(t_shell *s, int *idx)
{
	dstr_set(s->dstr, *idx, '\0');
	s->dstr->total = *idx;
	*idx -= 1;
}

void	quote_handler(t_shell *s, int *idx)
{
	char	c;

	c = s->dstr->buff[*idx];
	if (!s->isquote)
	{
		s->isquote = c;
		c == 34 ? index_table_dquote_init(s->spchar) :
		index_table_quote_init(s->spchar);
	}
	else
	{
		s->isquote = '\0';
		index_table_init(s->spchar);
	}
	dstr_remove(s->dstr, *idx, 1);
	*idx -= 1;
}

void	dollard_handler(t_shell *s, int *idx)
{
	char		*key;
	t_entry		*entry;
	uint32_t	i;
	uint32_t	j;

	if (s->dstr->buff[*idx + 1] == '$')
		return (ddollard_handler(s, idx));
	if (!ft_isalnum(s->dstr->buff[*idx + 1]))
		return ;
	i = *idx + 1;
	j = -1;
	key = (char[NAME_MAX]){0};
	while (ft_isalnum(s->dstr->buff[i]) || s->dstr->buff[i] == '_')
	{
		key[++j] = s->dstr->buff[i++];
		if (j == NAME_MAX - 1)
			break ;
	}
	dstr_remove(s->dstr, *idx, ft_strlen(key) + 1);
	entry = hashtable_get_entry(s->ht, key);
	if (entry && entry->item && (j = ft_strlen(entry->item)))
		dstr_join_str(s->dstr, entry->item, *idx);
	i = ft_strlen(key);
	*idx += j - i;
}

/*
**expand the '$$'by the value in the environment variable
**this doesn't work for single quotes
*/

void	ddollard_handler(t_shell *s, int *idx)
{
	char		*tmp;

	tmp = s->mt->track(&s->mt, ft_itoa(s->parent_id));
	dstr_remove(s->dstr, *idx, 2);
	dstr_join_str(s->dstr, tmp, *idx);
	*idx += ft_strlen(tmp) - 1;
}

/*
**Remove the backquote
*/

void	backslash_handler(t_shell *s, int *idx)
{
	dstr_remove(s->dstr, *idx, 1);
}

/*
**split the buffer by whitespace
**its replaces all the whitespaces by '\0'
**and return a pointer to the next non whitespace
*/

void	whitespace_handler(t_shell *s, int *idx)
{
	uint16_t	next;

	s->dstr->buff[*idx] = '\0';

	next = ft_strspn(&s->dstr->buff[*idx + 1], " \t\f\n\r");
	if (s->dstr->buff[*idx + next + 1])
		vector_add(s->cv, &s->dstr->buff[*idx + next + 1]);
	*idx += next;
}
