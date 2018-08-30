/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 20:15:37 by lkaba             #+#    #+#             */
/*   Updated: 2018/04/06 16:59:33 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_parse1(char *s, t_p *p)
{
	while (*s)
	{
		p->f.hash = *s == '#' ? 1 : p->f.hash;
		p->f.min = *s == '-' ? 1 : p->f.min;
		p->f.plus = *s == '+' ? 1 : p->f.plus;
		p->f.zero = *s == '0' ? 1 : p->f.zero;
		p->f.space = *s == ' ' ? 1 : p->f.space;
		if (!CE_5(*s, '#', '-', '+', ' ', '0'))
			break ;
		s++;
	}
	p->f.space = p->f.plus ? 0 : p->f.space;
	p->f.zero = p->f.min ? 0 : p->f.zero;
	return (ft_parse2(s, p));
}

int		accept_i_arg(char **s, t_p *p)
{
	int ret;

	ret = 0;
	while (ft_isdigit(**s))
	{
		ret = (10 * ret) + NUM(**s);
		(*s)++;
	}
	if (**s == '*')
	{
		ret = (int)va_arg(p->ap, int);
		(*s)++;
	}
	if (ft_isdigit(**s) || **s == '*')
		return (accept_i_arg(s, p));
	return (ret);
}

char	*ft_parse2(char *s, t_p *p)
{
	if (ft_isdigit(*s) || *s == '*')
		p->f.f_w = accept_i_arg(&s, p);
	if (*s == '.')
	{
		s++;
		p->f.prec = 1;
		p->f.zero = 0;
		p->f.precis = (unsigned int)accept_i_arg(&s, p);
	}
	return (ft_parse3(s, p));
}

char	*ft_parse3(char *s, t_p *p)
{
	int k;

	k = 1;
	((*s == 'h') && (*(s + 1) != 'h')) ? p->f.l = H : 1;
	((*s == 'l') && (*(s + 1) != 'l')) ? p->f.l = L : k;
	(*s == 'j') ? p->f.l = J : k;
	(*s == 'z') ? p->f.l = Z : k;
	if ((*s == 'h') && *(s + 1) == 'h')
	{
		p->f.l = HH;
		s++;
	}
	if ((*s == 'l') && *(s + 1) == 'l')
	{
		p->f.l = LL;
		s++;
	}
	if (CE_4(*s, 'h', 'l', 'j', 'z'))
		s++;
	return (ft_parse4(s, p));
}

char	*ft_parse4(char *s, t_p *p)
{
	if (CE_5(*s, 's', 'S', 'p', 'd', 'D') ||
		CE_5(*s, 'i', 'o', 'O', 'u', 'U') ||
		CE_5(*s, 'x', 'X', 'c', 'C', '%') ||
		*s == 'b')
	{
		p->f.type = *s;
		s++;
	}
	else
		return (s);
	ft_conversion(p);
	format_conversion(p);
	ft_precision(p);
	ft_field_width(p);
	ft_addnode(p, STR, p->f.len);
	return (s);
}
