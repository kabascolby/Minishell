/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sp_char_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:25:14 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/08 15:00:57 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hash_handler(t_shell *s, int *idx)
{
	if (!s->isquote)
	{
		dstr_set(s->dstr, *idx, '\0');
		dstr_set(s->dstr, *idx + 1, '\0');
		s->dstr->total = *idx - 1;
	}
}

void	quote_handler(t_shell *s, int *idx)
{
	char	c;

	if ((s->dstr->total > 1) && (dstr_get(s->dstr, *idx - 1) == 92))
		return ;
	c = dstr_get(s->dstr, *idx);
	if (s->isquote == c || !s->isquote)
		s->isquote = !s->isquote ? c : 0;
}

void	dollard_handler(t_shell *s, int *idx)
{
	char		*key;
	t_entry		*entry;
	uint32_t	i;
	uint32_t	j;

	if (s->dstr->buff[*idx + 1] == '$')
		return (ddollard_handler(s, idx));
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

void	ddollard_handler(t_shell *s, int *idx)
{
	char		*tmp;

	tmp = s->mt->track(&s->mt, ft_itoa(s->parent_id));
	dstr_remove(s->dstr, *idx, 2);
	dstr_join_str(s->dstr, tmp, *idx);
	*idx += ft_strlen(tmp) - 1;
}
