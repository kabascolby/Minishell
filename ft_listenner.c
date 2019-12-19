/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listenner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 01:18:17 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/19 00:48:09 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static t_bool		is_exectuble(char *path)
{
	struct stat sb;

	if (stat(path, &sb) == 0 && sb.st_mode & S_IXUSR)
		return (true);
	return (false);
}

static char	*find_exec(t_hashtable *ht, char *name)
{
	char	*env_paths;
	char	*save_ptr;
	char	*tmp;
	t_entry *e;

	if (!(e = ht->get_entry(ht, "PATH")) || !e->item)
		return (NULL);
	tmp = NULL;
	save_ptr = NULL;
	env_paths = ft_strdup(e->item);
	save_ptr = env_paths;
	while ((tmp = ft_strtok_r(save_ptr, ":", &save_ptr)))
	{
		dprintf(fd_num("/dev/ttys001"), "tmp->%s|s-->%s\n",tmp, save_ptr);
		if (!access((tmp = ft_join_args("", tmp, "/", name, 0)), F_OK | X_OK))
			break ;
	}
	free(env_paths);
	return (tmp);
}

static void		execute_process(t_command *p, t_hashtable *ht)
{
	char *path;

	p->id = getpid();
	path = (char *)p->vec->items[0];
	// dprintf(fd_num("/dev/ttys001"), "arg------->%s|\n", path);
	path = is_exectuble(path) ? path : find_exec(ht, path);
	if (-1 == (p->status = execve(path, (char **)p->vec->items, get_table(ht))))
		ft_errexit((char *)*p->vec->items, "invalide commmad", NULL);
	FREE(path);
	exit(0);
}

static void		execute_command(t_shell *s)
{
	t_command	*proc;
	t_command	**tmp;
	char		*name;
	int			p;
	int8_t		idx;

	proc = s->proc;
	while (proc)
	{
		name = s->mt->track(&s->mt, ft_strdup((char *)s->proc->vec->items[0]));
		ft_striter(name, ft_tolower2);
		idx = get_index(name, (char[]){BUILTINS});
		if (idx >= 0 && idx < s->fptr_len)
			proc->status = g_fptr[idx](s, proc->vec->total - 1,
			(char **)proc->vec->items + 1);
		else if (proc->vec->total && 0 == (p = fork()))
		{
			execute_process(proc, s->ht);
			vector_free(proc->vec);
			FREE(proc->vec);
			tmp = &proc;
			FREE(*tmp);
		}
		wait(&p);
		proc = proc->next;
	}
}

static t_bool	end_of_line(t_shell *s)
{
	char	c;

	if (read(STDIN_FILENO, &c, 1) > 0)
		g_keys[(int)index_char[(int)c]](s, c);
	return (s->is_readding);
}

void			stdin_listenner(t_shell *s)
{
	PROMPT;
	while (g_running)
	{
		if (!end_of_line(s) && !g_next_line)
			continue;
		dprintf(fd_num("/dev/ttys001"), "\nline------->%s|\n", s->dstr->buff);
		if (s->dstr->total > 0 && !g_next_line)
		{
			s->proc = MALLOC(sizeof(t_command));
			s->cmd = s->proc;
			s->cmd->vec = MALLOC(sizeof(t_vector));
			vector_init(s->cmd->vec);
			index_table_init(s->spchar);
			if (!ft_iswhitespace(s->dstr->buff[0]))
				vector_add(s->cmd->vec, s->dstr->buff);
			special_char_converter(s, 0);
			execute_command(s);
		}
		if (g_running)
		{
			//moving all those inside prompt comd
			if (g_next_line)
				g_next_line = false;
			s->is_readding = false;
			ft_memset((char *)s->dstr->buff, 0, s->dstr->capacity);
			s->dstr->total = 0;
			s->isquote = '\0';
			PROMPT;
		}
	}
}

/*
**TODO
**buffer has to be free only at the end of the program
**vector has to be free before the next readding process
**free the memory tracker
*/
