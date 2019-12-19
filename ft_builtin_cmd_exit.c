/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cmd_exit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:27:22 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/16 21:24:39 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_exit(t_shell *s, int argc, char **args)
{
	int	i;

	(void)s;
	if (argc > 1)
		return (ft_errexit(*(args - 1), "Expression Syntax.", 0));
	else if (argc == 1)
	{
		i = -1;
		while (args[0][++i])
		{
			if (!ft_isdigit(args[0][i]))
				return (ft_errexit(*(args - 1), "Badly formed number.", 0));
		}
	}
	g_running = false;
	return (0);
}
