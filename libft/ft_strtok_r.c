/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 01:52:42 by lkaba             #+#    #+#             */
/*   Updated: 2019/02/27 21:29:01 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok_r(char *s, const char *filter, char **save_ptr)
{
	char	*end;

	if (s == NULL)
		s = *save_ptr;
	if (*s == '\0')
	{
		*save_ptr = s;
		return (NULL);
	}
	s += ft_strspn(s, filter);
	if (*s == '\0')
	{
		*save_ptr = s;
		return (NULL);
	}
	end = s + ft_strcspn(s, filter);
	if (*end == '\0')
	{
		*save_ptr = end;
		return (s);
	}
	*end = '\0';
	*save_ptr = end + 1;
	return (s);
}
