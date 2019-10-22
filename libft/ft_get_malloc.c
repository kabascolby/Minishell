/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:23:16 by lkaba             #+#    #+#             */
/*   Updated: 2019/10/18 10:52:36 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_get_malloc(size_t n)
{
	void	*p;

	if (!((p) = ft_memalloc(n)))
	{
		ft_printf(ERROR_ALLOC_MESSAGE);
		exit(EXIT_FAILURE);
	}
	return (p);
}
