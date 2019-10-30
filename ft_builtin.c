/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 12:13:58 by lkaba             #+#    #+#             */
/*   Updated: 2019/10/28 23:23:00 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_env(t_shell *s, char **args)
{
	char **env;

	if (args && *args)
	{
		ft_errexit("env", "No such file or directory", *args, 0);
		return;
	}

	env = get_table(s->ht);
	if (env && *env)
		while (*env)
			ft_printf("%s\n", *env++);
	//TODO: free env
}

void	cmd_exit(t_shell *s, char **args)
{
	UNUSED(s, args);
	exit(1);
}
