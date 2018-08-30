/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:08:38 by lkaba             #+#    #+#             */
/*   Updated: 2017/11/22 16:08:39 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

inline static void	putlong(long n, int fd)
{
	if (n >= 10)
		putlong(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

void				ft_putnbr_fd(int n, int fd)
{
	long	v;

	v = n;
	if (v < 0)
	{
		ft_putchar_fd('-', fd);
		v = -v;
	}
	putlong(v, fd);
}
