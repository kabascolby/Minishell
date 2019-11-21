/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 01:45:12 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/19 19:36:34 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *str, const char *charset)
{
	uint32_t	i;
	uint32_t	count;
	uint8_t		tab[1024];

	ft_bzero(tab, 1024);

	i = -1;
		while(charset[++i])
		tab[(int)charset[i]] = 1;

	count = 0;
	i = 0;
	while (str[i] && !tab[(int)str[i++]])
		count++;
	return ((str[count] != '\0' && !tab[(int)str[count]]) ? count + 1 : count);
}
