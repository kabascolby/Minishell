/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errexit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 11:44:53 by lkaba             #+#    #+#             */
/*   Updated: 2019/10/31 19:54:33 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_errexit(const char *prog, char *errstr,
	const char *reason, uint8_t opt)
{
	write(STDERR_FILENO, prog, ft_strlen(prog));
	write(STDERR_FILENO, ": ", 2);
	if (reason)
	{
		write(STDERR_FILENO, reason, ft_strlen(reason));
		write(STDERR_FILENO, ": ", 2);
	}
	if (errstr)
		write(STDERR_FILENO, errstr, ft_strlen(errstr));
	write(STDERR_FILENO, "\n", 1);
	if (opt)
		exit(1);
}
