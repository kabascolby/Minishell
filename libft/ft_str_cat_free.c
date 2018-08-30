/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_cat_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 04:22:58 by lkaba             #+#    #+#             */
/*   Updated: 2018/07/10 04:23:44 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_cat_free(char **s, int j, char *s2)
{
	int			i;
	int			k;
	char		*str;

	k = 0;
	i = 0;
	if (!s2 || !*s2)
		return (*s);
	if (!(str = (char *)malloc(sizeof(char) *
		(ft_strlen(*s) + ft_strlen(s2)) + 1)))
		return (0);
	while (i < j - 1)
		str[i++] = (*s)[k++];
	while (*s2)
		str[i++] = *(s2++);
	while ((*s)[k])
		str[i++] = (*s)[k++];
	str[i] = '\0';
	ft_strdel(s);
	return (str);
}
