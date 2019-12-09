/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_substring.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 21:15:19 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/04 21:39:45 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**shift a string by triming a substring with the most accurate position
**if the substring is close to the front the trim will happen from the
**front else it will happen from the rear;
*/

char	*ft_shift_position(char *buf, uint32_t index, uint32_t size)
{
	uint32_t offset;
	uint32_t offset2;
	uint32_t len;

	len = ft_strlen(buf);
	if (!buf || !len || !size || (index >= len))
		return (buf);
	offset = &buf[index] - buf;
	offset2 = len - index;
	if (offset < (offset2 - size))
	{
		ft_memmove(&buf[size], buf, offset);
		offset = 0;
		while (offset < size)
			buf[offset++] = '\0';
		return (&buf[size]);
	}
	ft_memmove(&buf[index], buf + index + size, offset2);
	return (buf);
}
