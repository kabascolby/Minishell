/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:45:25 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/03 08:28:42 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Parsing the environement array to copy in my hashtable all the variables.
**Calling ft_strtok twice to split each line by equal sign
*/

void	parse_env(t_shell *s, char **env)
{
	char *key;
	char *value;

	while (*++env)
	{
		key = ft_strdup(ft_strtok_r(*env, "=", env));
		value = ft_strdup(ft_strtok_r(*env, "=", env));
		s->ht->insert(&s->ht, key, value);
	}
}

char	**split_line(char *line)
{
	char		**tokens;
	char		**tmp;
	uint16_t	bufsize;
	uint16_t	i;

	bufsize = TOK_BUFSIZE;
	tokens = MALLOC(bufsize * sizeof(char **));
	i = -1;
	while ((tokens[++i] = ft_strtok_r(line, FILTER, &line)) != NULL)
	{
		if (i + 1 >= TOK_BUFSIZE)
		{
			tmp = MALLOC(bufsize + TOK_BUFSIZE);
			ft_memcpy((char **)tmp, (char **)tokens, bufsize * sizeof(char *));
			bufsize += TOK_BUFSIZE;
			FREE(tokens);
			tokens = tmp;
			tmp = NULL;
		}
	}
	tokens[i] = NULL;
	return (tokens);
}
