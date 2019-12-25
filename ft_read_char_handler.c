/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_char_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 13:18:04 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/24 19:56:56 by lkaba            ###   ########.fr       */
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
**horizontal tabulation for autocompletion
*/

void	fn_tab(t_shell *s, char c)
{
	t_vector	*keys;
	char		*find;
	uint32_t	i;

	(void)c;
	keys = NULL;
	i = -1;
	hastable_keys(s->path, &keys);
	find = NULL;
	if (s->dstr->total && keys->total)
		while (keys->items[++i])
			if (!ft_strncmp(keys->items[i], s->dstr->buff, s->dstr->total))
				if (!find || ft_strlen(keys->items[i]) < ft_strlen(find))
					find = keys->items[i];
	if (find)
	{
		ft_putstr(find + s->dstr->total);
		dstr_join_str(s->dstr, find + s->dstr->total, s->dstr->total);
		s->pos = s->dstr->total;
	}
	vector_free(&keys);
}

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
**Delete input at any position
**this will be improved in 21sh
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

/*
**handling cursor mouvement
**this feature will be fully supported in 21sh
*/

static void	fn_up_and_down(t_shell *s, char c)
{
	if (!s->cur_hist && !s->dstr->total)
		write(1, "\033[s", 3);
	if (!s->cur_hist)
		s->cur_hist = s->history;
	if (c == 'A' && s->cur_hist->next)
		s->cur_hist = s->cur_hist->next;
	else if (c == 'B')
		s->cur_hist = s->cur_hist->prev;
	if (s->dstr->total && ft_memset(s->dstr->buff, 0, s->dstr->total))
	{
		ft_printf("%s%s", "\033[u", "\033[K");
		s->dstr->total = 0;
		s->pos = 0;
	}
	if (!s->cur_hist)
		return ;
	ft_putstr(s->cur_hist->data);
	ft_strcpy(s->dstr->buff, s->cur_hist->data);
	s->dstr->total = ft_strlen(s->dstr->buff);
	s->pos = s->dstr->total;
}


	// dprintf(ft_open_fd("/dev/ttys001"), "dire = %s| data = %d\n", (char *)s->history->data, s->dstr->total);

void	fn_with_esc(t_shell *s, char c)
{
	uint32_t			str_size;
	char				*tmp;

	(void)c;
	tmp = (char[4]){0};
	read(STDIN_FILENO, tmp, 4);
	if ((str_size = s->dstr->total) > 0)
	{
		tmp[1] == 'C' && str_size > s->pos ?
		write(1, "\033[C", 3) && s->pos++ : 0;
		tmp[1] == 'D' && s->pos > 0 ? write(1, "\033[D", 3) && --s->pos : 0;
	}

	if (tmp[1] == 'A' || tmp[1] == 'B')
		fn_up_and_down(s, tmp[1]);
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
