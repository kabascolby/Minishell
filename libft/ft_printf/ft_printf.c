/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 20:15:32 by lkaba             #+#    #+#             */
/*   Updated: 2018/04/04 19:16:05 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(char *s, ...)
{
	size_t		i;
	t_p			p;
	char		*s2;

	i = 0;
	if (!s || !(*s))
		return (0);
	ft_bzero(&p, sizeof(t_p));
	p.s3 = s;
	s2 = s;
	va_start(p.ap, s);
	while (*s && !(i = 0))
	{
		ft_bzero(&p.f, sizeof(t_args));
		while (s[i] && s[i] != '%')
			++i;
		ft_addnode(&p, ft_strdup(s2), i);
		if (s[i] == '%' && (s = ft_parse1(s + i + 1, &p)))
			s2 = s;
		else
			s = s + i;
	}
	va_end(p.ap);
	return (ft_nodeprint(&p));
}
