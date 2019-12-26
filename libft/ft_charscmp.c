/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charscmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 13:51:25 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 14:38:51 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_charscmp(int num, ...)
{
	va_list	args;
	int		a;
	int		b;
	int		i;
	int		j;

	va_start(args, num);
	a = va_arg(args, int);
	i = 0;
	j = 0;
	while (++i <= num)
	{
		b = va_arg(args, int);
		if (a == b)
		{
			j++;
			break ;
		}
	}
	va_end(args);
	return (j ? i : 0);
}
