/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cmd_cd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 10:32:05 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/17 11:53:46 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Check if the environment variables PWD and OLDPWD exist
**then update their value if not create them
*/

static int	update_env(t_shell *s)
{
	char	cwd[PATH_MAX];
	t_entry	*e;

	getcwd(cwd, PATH_MAX);
	if (!s->ht->get_entry(s->ht, "PATH"))
		hashtable_insert(&s->ht, ft_strdup("PATH"), ft_strdup(cwd));
	else
		hashtable_update(&s->ht, "PATH", ft_strdup(cwd));
	e = s->ht->get_entry(s->ht, "OLDPWD");
	if (!e)
		hashtable_insert(&s->ht, ft_strdup("OLDPWD"), ft_strdup(s->olpwd));
	if (!e->item)
		hashtable_update(&s->ht, "OLDPWD", ft_strdup(s->olpwd));
	return (0);
}

int			cmd_cd(t_shell *s, int argc, char **args)
{
	char	cwd[PATH_MAX];
	char	*path;
	char	*error;

	error = NULL;
	if (argc > 1)
		error = argc > 2 ? MANY : NOSTR;
	else if (!argc && chdir(s->ht->get_entry(s->ht, "HOME")->item))
		error = NODIR;
	else if (argc && !ft_strcmp(*args, "-"))
		error = !chdir(s->olpwd) && ft_printf("%s\n", s->olpwd) ? 0 : NOFDIR;
	else if (argc && (*args[0] != '/' || ft_strncmp(*args, "./", 2)))
	{
		if (!getcwd(cwd, PATH_MAX))
			error = NOPATH;
		else if (!(path = ft_join_args("", cwd, "/", *args, 0)) || chdir(path))
			(error = NOFDIR) && path ? free(path) : 0;
	}
	else
		chdir(*args);
	if (error)
		return (ft_errexit(*(args - 1), error, *args));
	else
		return (update_env(s));
}
