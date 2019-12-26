/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 13:18:04 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 16:36:40 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_char(t_shell *s, char c)
{
	char		tmp[2];
	uint32_t	cur;

	cur = 0;
	if (s->pos == s->dstr->total)
		dstr_add(s->dstr, c);
	else
	{
		tmp[0] = c;
		tmp[1] = '\0';
		write(1, "\033[K", 3);
		dstr_join_str(s->dstr, tmp, s->pos);
		ft_putstr(s->dstr->buff + s->pos + 1);
		cur = s->dstr->total;
		while (--cur > s->pos)
			write(1, "\033[D", 4);
	}
	s->pos++;
}

/*
**for all other key not handled
**the signal CTRL + D send end of file charactere to read
**this implementation will change slightly in 21sh
*/

void	fn_other_key(t_shell *s, char c)
{
	if (ft_isprint(c) && write(1, &c, 1))
		insert_char(s, c);
	if (s->old_t_attr.c_cc[VEOF] == c && !s->dstr->total)
	{
		recycled_bin(s);
		g_running = false;
	}
}

/*
**New line to stop the listeen process
*/

void	fn_new_line(t_shell *s, char c)
{
	if (s->isquote != '\0')
	{
		s->isquote == 34 ? write(1, "\ndquote> ", 9) :
		write(1, "\nquote> ", 8);
		insert_char(s, c);
	}
	else
	{
		write(1, "\n", 1);
		s->cur_hist = NULL;
		s->is_readding = true;
	}
}

/*
**Delete input
**basic implemention of line deletion
**this will be improved in 21sh to
*/

void	fn_delete(t_shell *s, char c)
{
	uint32_t	num;

	(void)c;
	if ((num = s->dstr->total) && s->pos)
	{
		if (s->isquote == dstr_get(s->dstr, s->pos - 1) && !((s->pos > 1) &&
		dstr_get(s->dstr, s->pos - 2) == 92))
			s->isquote = '\0';
		write(1, "\033[D", 3);
		write(1, "\033[K", 3);
		--s->pos;
		dstr_remove(s->dstr, s->pos, 1);
		ft_putstr(s->dstr->buff + s->pos);
		while (--num > s->pos)
			write(1, "\033[D", 3);
	}
}

void	fn_quote(t_shell *s, char c)
{
	uint32_t	num;

	insert_char(s, c);
	write(1, &c, 1);
	num = s->dstr->total;
	if (num > 1 && (dstr_get(s->dstr, num - 2) == 92))
		return ;
	if (s->isquote == c || s->isquote == '\0')
		s->isquote = !s->isquote ? c : 0;
}
