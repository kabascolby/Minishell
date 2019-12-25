/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:04:07 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/24 03:59:57 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_debug(char *s)
{
	if (s && ft_strlen(s) > 0)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd("\033[92m <--\n\033[0m", 2);
	}
	return (1);
}

int		ft_open_fd(char *device)
{
	static int fd;

	if (!fd && (fd = open(device, 1)) == -1)
	{
		ft_putendl("error opennig fd");
		return (0);
	}
	return (fd);
}
