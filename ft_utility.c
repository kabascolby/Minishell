/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 10:14:14 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/02 22:55:46 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	(*g_fptr[])(t_shell *, char **) =
{
	cmd_echo,
	cmd_cd,
	cmd_env,
	cmd_setenv,
	cmd_unsetenv,
	cmd_exit
};

char		**get_table(t_hashtable *ht)
{
	char		**tab;
	uint32_t	i;
	uint32_t	j;
	uint32_t	b;
	t_entry		*tmp;

	tab = (char **)malloc(sizeof(char *) * (ht->entries + 1));
	i = -1;
	j = -1;
	b = ht->num_buckets;
	while (++i < b)
	{
		if (ht->buckets[i])
		{
			tmp = ht->buckets[i];
			while (tmp)
			{
				tab[++j] = ft_join_args("=", tmp->key, tmp->item, NULL);
				tmp = tmp->next;
			}
			tab[j + 1] = NULL;
		}
	}
	return (tab);
}

int8_t		get_index(t_shell *s, char *cmd, ...)
{
	uint8_t	i;
	va_list	args;
	char	*t;

	va_start(args, cmd);
	i = 0;
	while (i < s->fptr_len && (t = va_arg(args, char *)))
	{
		if (SE_(t, cmd))
			break ;
		i++;
	}
	va_end(args);
	return (i ? i : -1);
}
