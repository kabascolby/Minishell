/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:05:31 by lkaba             #+#    #+#             */
/*   Updated: 2017/12/04 18:15:18 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(const char *s1, const char *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (0);
	return (ft_strnequ(s1, s2, ft_max(ft_strlen(s1), ft_strlen(s2))));
}
