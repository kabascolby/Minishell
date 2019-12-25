/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:08:01 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/24 12:12:04 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** (ctrl + c) signal handler
*/

static void		interrupt(int num)
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
	g_running = false;
	// write(STDOUT_FILENO, 0, 1);
}

/*
** (ctrl + Z) signal handler
*/

static void		ignore(int num)
{
	(void)num;
}

void	signal_handler(void)
{
	signal(SIGINT, interrupt);
	signal(SIGTERM, quit);
	signal(SIGTSTP, ignore);
	g_running = true;
	g_next_line = 0;
}
