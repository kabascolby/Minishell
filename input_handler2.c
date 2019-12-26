/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 11:41:38 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 16:41:23 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**horizontal tabulation for autocompletion
*/

void		fn_tab(t_shell *s, char c)
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

/*
**handling cursor mouvement
**this feature will be updated in 21sh
*/

static void	fn_up_and_down(t_shell *s, char c)
{
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

void		fn_with_esc(t_shell *s, char c)
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
