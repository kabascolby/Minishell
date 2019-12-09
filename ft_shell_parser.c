/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:45:25 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/08 20:46:00 by lkaba            ###   ########.fr       */
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

char	*token_handler(t_shell *s, char *line, const char *filter, char **save)
{
	char	*q;
	int		t;
	int		len;
	(void)s;

	t = ft_strcspn(line, filter);
	len = ft_srlen(line);


	if (line[t] == 34 || line[t] == 39)
	{
		q = line[t] == 34 ? "\"" : "\'";
	}
	return (ft_strtok_r(line," \t\f\n\r", save));
}

/*
**Using coumpound literral to create a char array and
**retuning a value to a pointer
*/


void split_line(t_shell *s, t_vector *v)
{
	const static char	*filters;
	char		*ptr;

	filters = (const char[]){' ', '\t', '\f', '\n', '\r', 34, 39, 0};

	while ((ptr = token_handler(s, s->dstr->buff, filters, &s->dstr->buff)))
		v->vector_add(v, ptr);
}

//todo write a malloc pointer tracker will mae your life easier
