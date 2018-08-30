/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoabase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 13:24:47 by lkaba             #+#    #+#             */
/*   Updated: 2018/04/06 13:35:18 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uitoabase(uintmax_t val, int base, int opt)
{
	static char buf[32];
	char		*set;
	int			i;
	int			o;

	set = NUMBERSET;
	i = 30;
	o = 0;
	if (opt != 0)
		o = 16;
	if (val == 0)
		return (ft_strdup("0"));
	while (val > 0 && i > 0)
	{
		buf[i] = set[(val % base) + o];
		val = val / base;
		--i;
	}
	return (ft_strdup(buf + i + 1));
}
