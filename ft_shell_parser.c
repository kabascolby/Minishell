/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:45:25 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/10 22:23:00 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Parsing the environement array to copy in my hashtable all the variables.
**Calling ft_strtok twice to split each line by equal sign
*/

void	parse_env(t_shell *s, char **env)
{
	char	*key;
	char	*value;
	t_entry	*shell_path;

	while (*++env)
	{
		key = ft_strdup(ft_strtok_r(*env, "=", env));
		value = ft_strdup(ft_strtok_r(*env, "=", env));
		s->ht->insert(&s->ht, key, value);
	}

	if (s->ht && (shell_path = s->ht->get_entry(s->ht, "SHELL")))
		s->ht->update(&s->ht, shell_path->key, "./minishell");
}

/*
** get the index of a special charactere, from that get the value
** of the special charactere in the spchar array.
** once the we got the value we can jump to the right function from
** the jumping table
*/

void	special_char_converter(t_shell *s, int32_t buf_idx)
{
	static sc_fptr	*fptr;
	int				idx;

	s->isquote = '\0';
	fptr = (sc_fptr[]){NULL, dollard_handler, hash_handler,
	quote_handler, backslash_handler, whitespace_handler};
	while (s->dstr->buff[buf_idx])
	{
		idx = s->spchar[(uint8_t)s->dstr->buff[buf_idx]];
		if (idx != 0)
			fptr[idx](s, &buf_idx);
		buf_idx++;
	}
}

//todo write a malloc pointer tracker will mae your life easier
