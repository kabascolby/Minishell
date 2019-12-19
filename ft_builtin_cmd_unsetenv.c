/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cmd_unsetenv.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 12:13:58 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/17 18:17:39 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_unsetenv(t_shell *s, int argc, char **args)
{
	int	i;

	i = -1;
	if (!argc)
		return (ft_errexit(*(args - 1), FEW, NULL));
	while (args[++i])
	{
		if (s->ht->get_entry(s->ht, args[i]))
			s->ht->pop_item(&s->ht, args[i]);
	}
	return (0);
}
