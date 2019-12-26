/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listenner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 01:18:17 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 12:02:47 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Check the if the argument is an executable then run it
**else find the argument in path hashtable and run it
*/

static void		execute_process(t_command *p, t_shell *s, char *error)
{
	t_entry	*entry;
	char	*path;

	p->child_pid = getpid();
	path = (char *)p->vec->items[0];
	entry = hashtable_get_entry(s->ht, "PATH");
	if ((access(path, F_OK | X_OK)) && entry && entry->item)
	{
		entry = hashtable_get_entry(s->path, path);
		path = entry && entry->item ? entry->item : path;
	}
	restor_terminal(s);
	if (-1 == (s->status = execve(path,
	(char **)p->vec->items, get_table(s->ht))))
	{
		ft_errexit(error, "invalide commmad", NULL);
	}
	free(error);
}

static void		execute_command(t_shell *s)
{
	t_command	**tmp;
	char		*name;
	int8_t		idx;

	while (s->proc && !g_next_line)
	{
		name = ft_strdup((char *)s->proc->vec->items[0]);
		ft_striter((char *)s->proc->vec->items[0], ft_tolower2);
		idx = get_index(s->proc->vec->items[0], (char[]){BUILTINS});
		if (idx >= 0 && idx < s->fptr_len)
			s->status = g_fptr[idx](s, s->proc->vec->total - 1,
			(char **)s->proc->vec->items + 1);
		else if (s->proc->vec->total && 0 == fork())
		{
			execute_process(s->proc, s, name);
			vector_free(&s->proc->vec);
			FREE(s->proc->vec);
			tmp = &s->proc;
			FREE(*tmp);
			exit(s->status);
		}
		waitpid(s->proc->child_pid, &s->status, 0);
		set_unbeffered();
		s->proc = s->proc->next;
	}
}

static t_bool	end_of_line(t_shell *s)
{
	char	c;

	if (read(STDIN_FILENO, &c, 1) > 0 && (int)c >= 0 && (int)c < 128)
		g_keys[(int)g_idx_char[(int)c]](s, c);
	return (s->is_readding);
}

static void		if_its_running(t_shell *s)
{
	if (g_next_line)
		g_next_line = false;
	s->is_readding = false;
	ft_memset((char *)s->dstr->buff, 0, s->dstr->capacity);
	s->dstr->total = 0;
	s->pos = 0;
	s->isquote = '\0';
	display_prompt(s);
}

void			stdin_listenner(t_shell *s)
{
	display_prompt(s);
	while (g_running)
	{
		if (!end_of_line(s) && !g_next_line)
			continue;
		dprintf(ft_open_fd("/dev/ttys001"), "\nline-->%s|\n", s->dstr->buff);
		if (s->dstr->total > 0 && !g_next_line)
		{
			pushdll(ft_strdup(s->dstr->buff), &s->history);
			s->proc = MALLOC(sizeof(t_command));
			s->cmd = s->proc;
			s->cmd->vec = MALLOC(sizeof(t_vector));
			vector_init(s->cmd->vec);
			index_table_init(s->spchar);
			if (!ft_iswhitespace(s->dstr->buff[0]) && s->dstr->buff[0] != ';')
				vector_add(s->cmd->vec, s->dstr->buff);
			special_char_converter(s, 0);
			execute_command(s);
		}
		if (g_running)
			if_its_running(s);
	}
}
