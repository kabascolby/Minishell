/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 01:45:39 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/24 21:58:45 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *str, const char *charset)
{
	uint32_t	i;
	uint32_t	count;
	uint8_t		tab[256];

	i = -1;
	ft_bzero(tab, 256);
	while (charset[++i])
		tab[(int)charset[i]] = 1;
	count = 0;
	i = 0;
	while (str[i] && tab[(int)str[i++]])
		count++;
	return ((str[count] != '\0' && tab[(int)str[count]]) ? count + 1 : count);
}
