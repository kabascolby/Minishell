/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 07:49:28 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/30 19:54:54 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_join_args(char *sep, ...)
{
	va_list		args;
	char		strdest[1024];
	char		*t;
	uint32_t	size;

	va_start(args, sep);
	ft_memset(strdest, 0, 1024);
	while ((t = va_arg(args, char *)))
	{
		if (t && *t)
		{
			ft_strcat(strdest, t);
			strdest[ft_strlen(strdest)] = *sep;
		}
	}
	if ((size = ft_strlen(strdest)))
		strdest[size] = 0;
	else
		return (NULL);
	va_end(args);
	return (ft_strdup(strdest));
}
