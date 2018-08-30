/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 17:57:32 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/31 14:15:20 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint64_t	ft_numdigit(uint64_t num)
{
	uint8_t cpt;

	cpt = 0;
	while (num != 0)
	{
		num /= 10;
		cpt++;
	}
	return (cpt);
}
