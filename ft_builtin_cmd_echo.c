/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cmd_echo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:40:11 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/23 11:50:10 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_echo(t_shell *s, int argc, char **args)
{
	(void)s;
	(void)argc;
	while (*args)
	{
		ft_putstr(*args++);
		if (*args)
			ft_putchar(' ');
	}
	ft_putstr("\n");
	return (0);
}
