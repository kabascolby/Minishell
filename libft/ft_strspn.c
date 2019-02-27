/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 01:45:39 by lkaba             #+#    #+#             */
/*   Updated: 2019/02/27 05:03:07 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *str, const char *charset)
{
	uint32_t	i;
	uint32_t	count;

	count = 0;
	i = 0;
	while (str[i] && ft_strchr(charset, str[++i]))
		count++;
	return (str[count] != '\0' && count) ? count + 1 : count;
}
