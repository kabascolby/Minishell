/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:03:02 by lkaba             #+#    #+#             */
/*   Updated: 2017/11/22 16:03:07 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		nbr;
	char	neg;

	while (ft_iswhitespace(*str))
		str++;
	neg = (*str == '-');
	if (*str == '-' || *str == '+')
		str++;
	nbr = 0;
	while (ft_isdigit(*str))
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	return (neg ? -nbr : nbr);
}
