/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sp_char_dispatcher.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 10:47:01 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/01 14:32:40 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** check if there there is special character in a s->dstr->buffing and return
** the index of the special charactere;
** if there is quote( ' or ") the backslash is off
** if there is backslash before the quote or dquote it's counted as
** a charactere.
*/

int32_t	is_spchar(t_shell *s, sc_fptr *ddollard_fptr)
{
	int32_t		*i;
	t_bool		is_q;
	t_bool		is_dq;

	is_q = 0;
	is_dq = 0;
	i = (int32_t[2]){-1, -1};
	while (s->dstr->buff[++i[0]])
	{
		if (CE_(s->dstr->buff[i[0]], '$') && (i[1] = i[0]) >= 0)
		{
			s->dstr->buff[i[0] + 1] == '$' ? *ddollard_fptr = ddollard_handler : 0;
			break ;
		}
		if (CE_(s->dstr->buff[i[0]], 34) && !is_q &&
		!(i[0] && CE_(s->dstr->buff[i[0] - 1], 92)))
			is_dq = is_dq ^ 1;
		if (CE_(s->dstr->buff[i[0]], 39) && !is_dq &&
		!(i[0] && CE_(s->dstr->buff[i[0] - 1], 92)))
			is_q = is_q ^ 1;
		if (CE_(s->dstr->buff[i[0]], '#') && !is_q && !is_dq && (i[1] = i[0]) >= 0)
			break ;
	}
	return (i[1]);
}

	// ft_printf("----> s->dstr->buff = %s\n", s->dstr->buff);
	// printf("%d | %d\n", i[0], i[1]);

/*
** get the index of a special charactere, from that get the value
** of the special charactere in the spchar array.
** once the we got the value we can jump to the right function from
** the jumping table
*/

void	special_char_converter(t_shell *s)
{
	static sc_fptr	*fptr;
	sc_fptr			quote_fptr;
	const char		*spchar;
	int32_t			idx;

	quote_fptr = dollard_handler;
	spchar = (char[127])SPCIDX;
	while ((idx = is_spchar(s, &quote_fptr)) != -1)
	{
		fptr = (sc_fptr[]){unhandled_spchar, quote_fptr, hash_handler};
		fptr[(int8_t)spchar[(int8_t)s->dstr->buff[idx]]](s, idx);
	}
}
