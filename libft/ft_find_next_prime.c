/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 19:00:31 by lkaba             #+#    #+#             */
/*   Updated: 2019/10/15 19:02:41 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint64_t	ft_find_next_prime(uint64_t n)
{
	if (ISEVEN(n))
		n++;
	else
		n += 2;
	while (!ft_isprime(n))
		n += 2;
	return (n);
}