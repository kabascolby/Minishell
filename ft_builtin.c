/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 12:13:58 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/14 18:45:31 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: check this function properly

void	cmd_cd(t_shell *s, char **args)
{
	char	*cwd;
	char	*path;
	char	*error;

	error = NULL;
	if (!*args && chdir(s->ht->get_entry(s->ht, "HOME")->item))
		error = NODIR;
	if (*args && *args[0] != '/' && (cwd = NULL))
	{
		if (NULL == getcwd(cwd, 145))
			error = NOPATH;
		if (!(path = ft_join_args("/", cwd, *args, NULL)) || -1 == chdir(path))
			error = NOFDIR;
		cwd ? free(cwd) : 0;
		path ? free(path) : 0;
	}
	else if ((*args && args[1]) || -1 == chdir(*args))
		error = args[1] ? NOSTR : NOFDIR;
	if (error)
		ft_errexit(*(args - 1), error, *args, 0);
}

void	cmd_echo(t_shell *s, char **args)
{
	UNUSED(s);
	while (*args)
		ft_putstr(*args++);
	ft_putstr("\n");
}

void	cmd_env(t_shell *s, char **args)
{
	char **env;

	if (args && *args)
	{
		ft_errexit("env", "No such file or directory", *args, 0);
		return ;
	}
	env = get_table(s->ht);
	if (env && *env)
		while (*env)
			ft_printf("%s\n", *env++);
	//TODO: free env
}


//TODO: create a new environment if the env is NULL

void	cmd_setenv(t_shell *s, char **args)
{
	int	i;

	i = -1;
	if (!*args)
		return (cmd_env(s, args));
	if (!ft_isalpha(*args[0]))
		return (ft_errexit(*(args - 1), BAD_VAR, NULL, 0));
	while (args[0][++i])
		if (!ft_isalnum(args[0][i]))
			return (ft_errexit(*(args - 1), ONLYALPHA_NUM, NULL, 0));
	if (!args[1])
	{
		s->ht->get_entry(s->ht, *args) ? s->ht->update(&s->ht, *args,
		ft_strdup("")) : s->ht->insert(&s->ht, ft_strdup(*args), ft_strdup(""));
		return ;
	}
	if (args[1] && args[2])
		return (ft_errexit(*(args - 1), "Too many arguments.", NULL, 0));
	s->ht->get_entry(s->ht, *args) ? s->ht->update(&s->ht, *args,
	ft_strdup(args[1])) : s->ht->insert(&s->ht,
	ft_strdup(*args), ft_strdup(args[1]));
}

void	cmd_unsetenv(t_shell *s, char **args)
{
	int	i;

	i = -1;
	if (!*args)
		return (ft_errexit(*(args - 1), "Too few arguments.", NULL, 0));
	while (args[++i])
	{
		if (s->ht->get_entry(s->ht, args[i]))
		{
			ft_putendl(args[i]);
			s->ht->pop_item(&s->ht, args[i]);
		}
	}
}

void	cmd_exit(t_shell *s, char **args)
{
	UNUSED(args, s);
	// if(s->line)
	// 	FREE(s->line);
	//TODO make sure to free all the buckets
	exit(1);
}
