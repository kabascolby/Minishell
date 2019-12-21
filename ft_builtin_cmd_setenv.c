/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cmd_setenv.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:56:07 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/19 23:30:09 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_setenv(t_shell *s, int argc, char **args)
{
	int	i;

	if (argc > 2)
		return (ft_errexit(*(args - 1), MANY, NULL));
	if (!argc)
		return (cmd_env(s, argc, args));
	if (!ft_isalpha(*args[0]))
		return (ft_errexit(*(args - 1), BAD_VAR, NULL));
	i = -1;
	while (args[0][++i])
		if (!ft_isalnum(args[0][i]))
			return (ft_errexit(*(args - 1), ONLYALPHA_NUM, NULL));
	if (argc == 1)
	{
		s->ht->get_entry(s->ht, *args) ? s->ht->update(&s->ht, *args,
		ft_strdup("")) : s->ht->insert(&s->ht, ft_strdup(*args), ft_strdup(""));
		return (0);
	}
	s->ht->get_entry(s->ht, *args) ? s->ht->update(&s->ht, *args,
	ft_strdup(args[1])) : s->ht->insert(&s->ht,
	ft_strdup(*args), ft_strdup(args[1]));
	if (!ft_strcmp(*args, "PATH"))
		parse_executable(s);
	return (0);
}
