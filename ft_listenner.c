/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listenner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 01:18:17 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/02 12:55:41 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void stdin_listenner(t_shell *s)
{
	t_process	proc;
	static char	*path;
	int8_t		idx;
	int			p;

	PROMPT;
	ft_bzero((t_process *)&proc, sizeof(t_process));
	if (get_next_line(1, &s->line) > 0)
	{
		proc.tokens = split_line(s->line);
		idx = get_index(s, proc.tokens[0], TOKENS);
		printf("line----------->%s | %d\n", s->line, idx);
		if (idx >= 0 && idx < s->fptr_len)
		{
			s->fptr[idx](s, proc.tokens + 1);
			// FREE(s->line);
		}
		else if (0 == (p = fork()) && proc.tokens[0])
		{
			//TODO: get the rignt binary file
			path = ft_join_args("/", _PATH_BSHELL, *proc.tokens, NULL);
			// ft_printf("_____child_____________%d___%d\n", getpid(), p);
			if (-1 == execve(path, proc.tokens, get_table(s->ht)))
				ft_putendl("invalide commmad");
			FREE(s->line);
		}
		else
		{
			wait(&p);
			// ft_printf("________________parent________%d___%d\n", getpid(), p);
		}
		stdin_listenner(s);
	}
}
