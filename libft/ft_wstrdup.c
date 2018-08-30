/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 13:37:51 by lkaba             #+#    #+#             */
/*   Updated: 2018/04/06 13:40:11 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

wchar_t		*ft_wstrdup(wchar_t *ws)
{
	wchar_t		*tmp;
	int			i;

	if (!ws)
		return (NULL);
	i = -1;
	while (ws[++i])
		;
	if (!(tmp = (wchar_t *)ft_strnew(sizeof(wchar_t) * i)))
		return (NULL);
	i = -1;
	while (ws[++i])
		tmp[i] = ws[i];
	tmp[i] = L'\0';
	return (tmp);
}
