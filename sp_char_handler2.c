/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_char_handler2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 12:09:05 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 16:37:21 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Comment everi=ything after the Hash
*/

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

/*
**Handling multiple commands separate by semy columns
*/

void	semicolon_handler(t_shell *s, int *idx)
{
	t_command	**nc;
	t_command	*tmp;
	uint16_t	next;
	char		c;

	next = 0;
	if (*idx > 1 && !ft_iswhitespace(s->dstr->buff[*idx - 1]))
		s->dstr->buff[*idx] = '\0';
	next = ft_strspn(&s->dstr->buff[*idx + 1], " ;\t\f\n\r");
	c = s->dstr->buff[*idx + next + 1];
	if (c)
	{
		tmp = s->proc;
		while (tmp)
		{
			nc = &tmp->next;
			tmp = tmp->next;
		}
		*nc = MALLOC(sizeof(t_command));
		s->cmd = *nc;
		s->cmd->vec = MALLOC(sizeof(t_vector));
		vector_init(s->cmd->vec);
		vector_add(s->cmd->vec, &s->dstr->buff[*idx + next + 1]);
	}
	*idx += next;
}
