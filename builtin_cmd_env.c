/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cmd_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:00:03 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 16:31:45 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_env(t_shell *s, int argc, char **args)
{
	char **env;

	if (argc)
		return (ft_errexit("env", "No such file or directory", *args));
	env = get_table(s->ht);
	if (env && *env)
		while (*env)
			ft_putendl(*env++);
	return (0);
}
