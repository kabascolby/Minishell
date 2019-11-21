/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:08:01 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/08 19:41:45 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** (ctrl + c) signal handler
*/

static void		ignore(int num)
{
	UNUSED(num);
	//TODO: call exit here make sure everithing is free
	//exit the process an call the main and display the prompt
	ft_putendl("I'm here for to make it work");
}

/*
** (ctrl + d) signal handler
*/

static void		quit(int num)
{
	UNUSED(num);
	ft_putendl("I'm gonna stop everything");
}

void	signal_handler(void)
{
	signal(SIGINT, ignore);
	signal(SIGTERM, quit);
}
