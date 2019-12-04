/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sp_char_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:25:14 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/03 18:29:27 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hash_handler(t_shell *s, int idx)
{
	UNUSED(s);
	s->dstr->buff[idx] = '\0';
	s->dstr->dstr_set(s->dstr, idx, '\0');
}

void	quote_handler(t_shell *s, int idx)
{
	UNUSED(s, idx);
	ft_putendl("i'm inside double quote");
}

void	dquote_handler(t_shell *s, int idx)
{
	UNUSED(s, idx);
	ft_putendl("i'm inside double quote");
}

void	dollard_handler(t_shell *s, int idx)
{
	/*char		*buff;
	 uint16_t		i;
	uint16_t		j;
	char		*tmp;
	uint16_t	capacity;

	capacity = 100;
	i = idx;
	j = -1;

	buff = MALLOC(capacity);*/
	UNUSED(s, idx);
	// while (ft_isalnum(s->dstr->buff[++i]) || s->dstr->buff[idx])
	// {
	// 	if(++j + 1 >= capacity);
	// }
}

void	ddollard_handler(t_shell *s, int idx)
{
	char		*tmp;

	s->dstr->buff[idx] = '\0';
	tmp = ft_join_args("", s->dstr->buff, s->mt->track(&s->mt,
	ft_itoa(s->parent_id)), &s->dstr->buff[idx + 2], NULL);
	free(s->dstr->buff);
	s->dstr->buff = tmp;
	tmp = NULL;
}

void	unhandled_spchar(t_shell *s, int idx)
{
	UNUSED(s, idx);
	ft_putendl("not handled on my side");
}
