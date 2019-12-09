/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sp_char_dispatcher.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 10:47:01 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/08 19:09:52 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** get the index of a special charactere, from that get the value
** of the special charactere in the spchar array.
** once the we got the value we can jump to the right function from
** the jumping table
*/

void	special_char_converter(t_shell *s)
{
	static sc_fptr	*fptr;
	int32_t			i;
	int				idx;

	i = -1;
	s->isquote = '\0';
	fptr = (sc_fptr[]){NULL, dollard_handler, hash_handler, quote_handler};
	while (s->dstr->buff[++i])
	{
		idx = g_spchar[(uint8_t)s->dstr->buff[i]];
		if (idx != 0)
			fptr[idx](s, &i);
	}
}
