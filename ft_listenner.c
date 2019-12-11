/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listenner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 01:18:17 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/10 22:26:54 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	nothing(int num)
{
	UNUSED(num);
	write(1, "nothing\n", 8);
}

static void	create_process(t_shell *s)
{
	static char *path;

	s->proc->id = getpid();
	path = ft_join_args("", _PATH_BSHELL, "/", *s->proc->vec->items, NULL);
	if (-1 == (s->proc->status =
	execve(path, (char **)s->proc->vec->items, get_table(s->ht))))
		ft_errexit((char *)*s->proc->vec->items, "invalide commmad", NULL, 0);
	FREE(path);
	exit(0);
}

static int16_t	read_stdin(t_shell *s)
{
	char	c;

	ft_memset((char *)s->dstr->buff, 0, s->dstr->capacity);
	dstr_init(s->dstr);
	s->dstr->total = 0;
	s->isquote = '\0';
	while (s->is_readding && (read(STDIN_FILENO, &c, 1)) > 0)
		g_keys[(int)index_char[(int)c]](s, c, write);
	return (true);
}

void	stdin_listenner(t_shell *s)
{
	int8_t		idx;
	int			p;
	t_command	*proc;

	PROMPT;
	s->is_readding = true;
	if (read_stdin(s))
	{
		dprintf(fd_num("/dev/ttys001"), "\nline------->%s|\n", s->dstr->buff);
		s->proc->vec = MALLOC(sizeof(t_vector));
		vector_init(s->proc->vec);
		s->cv = s->proc->vec;
		index_table_init(s->spchar);
		if (s->dstr->total)
			vector_add(s->cv, s->dstr->buff);
		special_char_converter(s, 0);
		proc = s->proc;
		while (proc)
		{
			idx = get_index(s, (char *)s->proc->vec->items[0], TOKENS);
			if (idx >= 0 && idx < s->fptr_len)
				g_fptr[idx](s, (char **)s->proc->vec->items + 1);
			else if (0 == (p = fork()) && (char *)s->proc->vec->items[0])
				create_process(s);
			wait(&p);
			proc = proc->next;
		}
		stdin_listenner(s);
	}
}

// TODO
		// split_line(s, vec);
// vector is malloc |items in vector is malloc| buffer string is malloc|
// ft_printf("_____child_____________%d___%d\n", getpid(), p);
// ft_printf("________________parent________%d___%d\n", getpid(), p);
// s->old_t_attr.c_cc[VERASE] == c
