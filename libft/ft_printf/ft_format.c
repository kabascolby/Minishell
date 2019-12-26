/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 17:36:05 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 18:08:48 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** if the flag zero is on then the field width is replaced by zero
** '0' is ignnored when '-' is present;
** the space depends also to the minus sign
** space is ignnored when '+' is on
** replace "length" by "l"
** replace "string split free  ft_frsplitstr" by "ft_spf"
*/

void	ft_precision(t_p *p)
{
	char f[p->f.precis ? p->f.precis + 1 : 1];

	if (!p->f.prec)
		return ;
	if ((CE(5, p->f.type, 'd', 'i', 'D', 'o', 'O') ||
				CE(5, p->f.type, 'x', 'X', 'p', 'u', 'U')) && p->f.precis)
	{
		p->f.zero = 0;
		p->f.precis = (p->f.precis < p->f.len - p->f.sign) ?
			0 : p->f.precis - p->f.len + p->f.sign;
		f[p->f.precis] = '\0';
		ft_memset((char *)f, '0', p->f.precis);
		STR = ft_spf(&STR, 1 + p->f.sign, f);
	}
	if ((CE(2, p->f.type, 's', 'S')) && (p->f.precis < ft_strlen(STR)))
		ft_memset((char *)&STR[p->f.precis], 0, 1);
}

void	ft_field_width(t_p *p)
{
	char f[p->f.f_w ? p->f.f_w + 1 : 1];

	p->f.f_w -= (!p->f.types.c && CE(2, p->f.type, 'c', 'C') &&
		p->f.f_w > 0) ? 1 : 0;
	STR = (p->f.space && CE(2, p->f.type, 'd', 'i') && !p->f.sign) ?
		ft_spf(&STR, 1, " ") : STR;
	p->f.plus ? STR = ft_spf(&STR, 1, "+") : 0;
	p->f.len = ft_strlen(STR);
	p->f.f_w = (p->f.f_w < p->f.len) ? 0 : p->f.f_w - p->f.len;
	p->f.f_w -= ((p->f.hash && p->f.f_w &&
		CE(2, p->f.type, 'x', 'X')) || p->f.type == 'p') ? 2 : 0;
	p->f.f_w -= (p->f.hash && p->f.f_w && CE(2, p->f.type, 'o', 'O')) ? 1 : 0;
	p->f.f_w = p->f.f_w < 0 ? 0 : p->f.f_w;
	f[p->f.f_w] = '\0';
	p->f.fw = p->f.zero ? '0' : ' ';
	ft_memset(f, p->f.fw, p->f.f_w);
	STR = p->f.zero ? ft_spf(&STR, 1 + p->f.sign + p->f.plus, f) : STR;
	p->f.pos = p->f.min ? (p->f.len + 1) : (int)(1 - p->f.sign);
	STR = !p->f.zero ? ft_spf(&STR, p->f.pos, f) : STR;
	ft_field_width2(p);
}

void	ft_field_width2(t_p *p)
{
	char *s;

	if (CE(2, p->f.type, 'o', 'O') && p->f.hash)
	{
		p->f.pos = p->f.min ? 1 : 1 + p->f.f_w;
		STR = STR[0] != '0' ? ft_spf(&STR, p->f.pos, "0") : STR;
	}
	if ((CE(2, p->f.type, 'x', 'X') && p->f.hash) || (p->f.type == 'p'))
	{
		s = p->f.type == 'X' ? "0X" : "0x";
		p->f.pos = !p->f.zero && !p->f.min ? p->f.f_w + 1 : 1;
		STR = p->f.types.um || p->f.type == 'p' ?
		ft_spf(&STR, p->f.pos, s) : STR;
	}
	p->f.len = ft_strlen(STR);
}
