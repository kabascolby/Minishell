/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 04:13:13 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/26 09:41:55 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_conversion(t_p *p)
{
	if (((p->f.type == 's') && (p->f.l == L)) || ((p->f.type == 'S')))
	{
		p->f.types.ws = ft_wstrdup((wchar_t *)va_arg(p->ap, wchar_t *));
		!(p->f.types.ws) ? p->f.types.ws = ft_wstrdup(L"(null)") : 0;
	}
	else if (((p->f.type == 'c') && (p->f.l == L)) || ((p->f.type == 'C')))
		p->f.types.wc = (wchar_t)va_arg(p->ap, wchar_t);
	else if (p->f.type == 's')
	{
		STR = ft_strdup((char *)va_arg(p->ap, char *));
		STR = !(STR) ? ft_strdup("(null)") : STR;
	}
	else if (CE(3, p->f.type, 'd', 'i', 'D'))
		IM = (int64_t)va_arg(p->ap, int64_t);
	else if ((CE(5, p->f.type, 'o', 'u', 'x', 'O', 'U')) ||
			(CE(3, p->f.type, 'X', 'p', 'b')))
		p->f.types.um = (uintmax_t)va_arg(p->ap, uintmax_t);
	else if (p->f.type == '%')
		STR = ft_strdup("%");
	else if (p->f.type == 'c')
		p->f.types.c = (char)va_arg(p->ap, int);
	else
		return ;
	p->f.l = CE(5, p->f.type, 'D', 'O', 'U', 'S', 'C') ||
		(p->f.type == 'p') ? L : p->f.l;
}

void	format_conversion(t_p *p)
{
	int i;

	if (CE(3, p->f.type, 'd', 'i', 'D'))
	{
		((int)IM < 0) ? p->f.sign = 1 : 0;
		p->f.plus = p->f.sign ? 0 : p->f.plus;
		STR = (!p->f.l) ? ft_itoa((int)p->f.types.im) : STR;
		STR = (p->f.l == H) ? ft_itoa((short)p->f.types.im) : STR;
		STR = (p->f.l == HH) ? ft_itoa((signed char)p->f.types.im) : STR;
		STR = (p->f.l == L) ? ft_itoa((long)p->f.types.im) : STR;
		STR = (p->f.l == LL) ? ft_itoa((long long)p->f.types.im) : STR;
		STR = (p->f.l == J) ? ft_itoa((int64_t)p->f.types.im) : STR;
		STR = (p->f.l == Z) ? ft_itoa((ssize_t)p->f.types.im) : STR;
		STR[0] = IM == 0 && p->f.prec && !p->f.precis ? '\0' : STR[0];
	}
	if (((p->f.type == 's') && (p->f.l == L)) || (p->f.type == 'S'))
	{
		i = -1;
		while (p->f.types.ws[++i] || !(STR = ft_strnew(i)))
			;
		while (i-- > -1)
			STR[i] = (char)p->f.types.ws[i];
		free(p->f.types.ws);
	}
	format_conversion2(p);
}

void	format_conversion2(t_p *p)
{
	if (CE(2, p->f.type, 'u', 'U'))
	{
		p->f.plus = 0;
		STR = (!p->f.l) ? UIB((uint32_t)p->f.types.um, 10, 0) : STR;
		STR = (p->f.l == H) ? UIB((uint16_t)
		p->f.types.um, 10, 0) : STR;
		STR = (p->f.l == HH) ? UIB((uint8_t)
		p->f.types.um, 10, 0) : STR;
		STR = (p->f.l == L) ? UIB((uintmax_t)
		p->f.types.um, 10, 0) : STR;
		STR = (p->f.l == LL) ? UIB((uint64_t)
		p->f.types.um, 10, 0) : STR;
		STR = (p->f.l == J) ? UIB((uintmax_t)p->f.types.um, 10, 0) : STR;
		STR = (p->f.l == Z) ? UIB((size_t)p->f.types.um, 10, 0) : STR;
		STR[0] = p->f.types.um == 0 && p->f.prec &&
		!p->f.precis ? '\0' : STR[0];
		if (p->f.types.um == 0 && !p->f.prec)
		{
			free(STR);
			STR = ft_strdup("0");
		}
	}
	format_conversion3(p);
}

void	format_conversion3(t_p *p)
{
	if (CE(2, p->f.type, 'o', 'O'))
	{
		STR = (!p->f.l) ? UIB((uint32_t)p->f.types.um, 8, 0) : STR;
		STR = (p->f.l == H) ? UIB((uint16_t)p->f.types.um, 8, 0) : STR;
		STR = (p->f.l == HH) ? UIB((uint8_t)p->f.types.um, 8, 0) : STR;
		STR = (p->f.l == L) ? UIB((uintmax_t)p->f.types.um, 8, 0) : STR;
		STR = (p->f.l == LL) ? UIB((uint64_t)p->f.types.um, 8, 0) : STR;
		STR = (p->f.l == J) ? UIB((uintmax_t)p->f.types.um, 8, 0) : STR;
		STR = (p->f.l == Z) ? UIB((size_t)p->f.types.um, 8, 0) : STR;
		p->f.types.um == 0 && p->f.prec && !p->f.precis ? STR[0] = '\0' : 0;
		if (p->f.types.um == 0 && !p->f.prec)
		{
			free(STR);
			STR = ft_strdup("0");
		}
		STR = !p->f.types.um && p->f.hash && !p->f.precis ?
		ft_memcpy(STR, "0", 2) : STR;
	}
	if (((p->f.type == 'c') && (p->f.l == L)) || ((p->f.type == 'C')))
	{
		STR = ft_strnew(1);
		STR[0] = (char)p->f.types.wc;
	}
	format_conversion4(p);
}

void	format_conversion4(t_p *p)
{
	if (p->f.type == 'c')
	{
		STR = ft_strnew(1);
		STR[0] = p->f.types.c;
	}
	if (CE(3, p->f.type, 'x', 'X', 'p'))
	{
		STR = (!p->f.l) ? UIB((uint32_t)p->f.types.um, 16, 0) : STR;
		STR = (p->f.l == H) ? UIB((uint16_t)p->f.types.um, 16, 0) : STR;
		STR = (p->f.l == HH) ? UIB((uint8_t)p->f.types.um, 16, 0) : STR;
		STR = (p->f.l == L) ? UIB((uintmax_t)p->f.types.um, 16, 0) : STR;
		STR = (p->f.l == LL) ? UIB((uint64_t)p->f.types.um, 16, 0) : STR;
		STR = (p->f.l == J) ? UIB((uintmax_t)p->f.types.um, 16, 0) : STR;
		STR = (p->f.l == Z) ? UIB((size_t)p->f.types.um, 16, 0) : STR;
		STR = p->f.type == 'X' ? ft_strupcase(STR) : STR;
		p->f.types.um == 0 && p->f.prec && !p->f.precis ? STR[0] = '\0' : 0;
		if (p->f.types.um == 0 && !p->f.prec)
		{
			free(STR);
			STR = ft_strdup("0");
		}
	}
	STR = p->f.type == 'b' ? UIB((uint64_t)p->f.types.um, 2, 0) : STR;
	p->f.len = CE(2, p->f.type, 'c', 'C') ? 1 : ft_strlen(STR);
}
