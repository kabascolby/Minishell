/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:45:25 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 16:39:29 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Parsing the environement array to copy in my hashtable all the variables.
**Calling ft_strtok twice to split env_ptr line by equal sign
*/

void		parse_env(t_shell *s, char **env)
{
	char	*key;
	char	*value;
	t_entry	*shell_path;

	while (*++env)
	{
		key = ft_strtok_r(*env, "=", env);
		value = ft_strtok_r(*env, "=", env);
		s->ht->insert(&s->ht, ft_strdup(key), ft_strdup(value));
	}
	if (s->ht && (shell_path = s->ht->get_entry(s->ht, "SHELL")))
		s->ht->update(&s->ht, shell_path->key, ft_strdup("./minishell"));
}

/*
**Grab all the executables from a given directory
**and build an abolute path in an Hashtable path.
*/

static void	save_executables(t_shell *s, char *path, DIR *dir)
{
	struct dirent	*entry;
	char			*abs_path;

	while ((entry = readdir(dir)))
	{
		if (entry->d_name[0] == '.')
			continue ;
		abs_path = ft_join_args("", path, "/", entry->d_name, NULL);
		if (access(abs_path, F_OK | X_OK))
		{
			free(abs_path);
			continue ;
		}
		hashtable_insert(&s->path, ft_strdup(entry->d_name), abs_path);
	}
}

/*
**split the path enviroment variable by ':'
**for each path open the directory
**adding builtin to path for auto completion
*/

void		parse_executable(t_shell *s)
{
	t_entry *entry;
	char	*save_env;
	char	*env_ptr;
	char	*path;
	DIR		*dir;

	if (!(entry = s->ht->get_entry(s->ht, "PATH")) || !entry->item)
		return ;
	save_env = ft_strdup(entry->item);
	env_ptr = save_env;
	s->path = hashtable_init(300);
	while ((path = ft_strtok_r(env_ptr, ":", &env_ptr)))
		if ((dir = opendir(path)))
		{
			save_executables(s, path, dir);
			closedir(dir);
		}
	FREE(save_env);
	env_ptr = (char[]){BUILTINS};
	while ((path = ft_strtok_r(env_ptr, " ", &env_ptr)))
		hashtable_insert(&s->path, ft_strdup(path), ft_strdup(path));
}

/*
** get the index of a special charactere, from that get the value
** of the special charactere in the spchar array.
** once the we got the value we can jump to the right function from
** the jumping table
*/

void		special_char_converter(t_shell *s, int32_t buf_idx)
{
	static t_sc_fptr	*fptr;
	int					idx;

	s->isquote = '\0';
	fptr = (t_sc_fptr[]){NULL, dollard_handler, hash_handler,
	quote_handler, backslash_handler, whitespace_handler,
	semicolon_handler, backslash_tilde};
	while (s->dstr->buff[buf_idx])
	{
		idx = s->spchar[(uint8_t)s->dstr->buff[buf_idx]];
		if (idx != 0)
			fptr[idx](s, &buf_idx);
		buf_idx++;
	}
}
