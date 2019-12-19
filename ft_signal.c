/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:08:01 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/13 19:32:18 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** (ctrl + c) signal handler
*/

static void		ignore(int num)
{
	(void)num;
	g_next_line = true;
	write(STDOUT_FILENO, "\n", 1);
}

/*
** (ctrl + d) signal handler
*/

static void		quit(int num)
{
	UNUSED(num);
	write(STDOUT_FILENO, 0, 1);
	// printf("%d\n", g_running);
}

void	signal_handler(void)
{
	signal(SIGINT, ignore);
	signal(SIGTERM, quit);
	g_running = true;
	g_next_line = 0;
}
