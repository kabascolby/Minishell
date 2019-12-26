/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_char_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:25:14 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 16:38:07 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
**Expand the '$$'by the value in the environment variable
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
	char		c;

	if (s->dstr->buff[*idx] == ';')
		return ;
	s->dstr->buff[*idx] = '\0';
	next = ft_strspn(&s->dstr->buff[*idx + 1], " \t\f\n\r");
	c = s->dstr->buff[*idx + next + 1];
	if (c && c != ';')
		vector_add(s->cmd->vec, &s->dstr->buff[*idx + next + 1]);
	*idx += next;
}

/*
**Replace the tidle by the home variable
**this will be updated in 21sh
*/

void	backslash_tilde(t_shell *s, int *idx)
{
	t_entry	*e;
	char	*home;

	if (*idx > 0 && s->dstr->buff[*idx - 1] &&
	!ft_iswhitespace(s->dstr->buff[*idx - 1]))
		return ;
	e = s->ht->get_entry(s->ht, "HOME");
	home = e && e->item ? e->item : "";
	dstr_remove(s->dstr, *idx, 1);
	dstr_join_str(s->dstr, home, *idx);
	*idx += ft_strlen(home) - 1;
}
