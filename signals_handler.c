/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:08:01 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 16:40:45 by lkaba            ###   ########.fr       */
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
	(void)num;
	g_running = false;
}

/*
** (ctrl + Z) signal handler
*/

static void		ignore(int num)
{
	(void)num;
}

void			signal_handler(void)
{
	signal(SIGINT, interrupt);
	signal(SIGTERM, quit);
	signal(SIGTSTP, ignore);
	g_running = true;
	g_next_line = 0;
}
