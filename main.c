/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 10:04:57 by lkaba             #+#    #+#             */
/*   Updated: 2019/10/30 10:41:12 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

void stdin_listenner(t_shell *s)
{
	char		*line;
	t_process	proc;
	static char	*path;
	int8_t		idx;
	int 		p;
	// char *newenviron[] = { NULL };

	PROMPT;
	line = NULL;
	ft_bzero((t_process *)&proc, sizeof(t_process));
	if (get_next_line(1, &line) > 0)
	{
		printf("line----------->%s\n",line);
		proc.tokens = split_line(line);

		if((idx = get_index(s, proc.tokens[0], TOKENS)) >= 0 && idx < s->fptr_len)
			s->fptr[idx](s, proc.tokens + 1);
		else if (0 == (p = fork()) && proc.tokens[0])
		{
			path = ft_join_args("/", _PATH_BSHELL, *proc.tokens, NULL);
			ft_printf("________________child_____________%d___%d\n", getpid(), p);
			if(-1 == execve(path, proc.tokens, environ))
				ft_putendl("invalide commmad");
		}
		else
		{
			wait(&p);
			ft_printf("________________parent________%d___%d\n", getpid(), p);
		}
		stdin_listenner(s);
	}
}

int main()
{
	t_shell	shell;
	ft_bzero((t_shell *)&shell, sizeof(t_shell));
	shell.ht = hashtable_init(INIT_HASHTABLE_SIZE);
	parse_env(&shell, environ);
	shell.fptr_len = (uint8_t)sizeof(shell.fptr) / sizeof(*shell.fptr);
	// shell.fptr = {cmd_echo, cmd_cd, cmd_unsetenv, cmd_env, cmd_exit};
	shell.fptr[3] = cmd_env;
	shell.fptr[4] = cmd_exit;
	stdin_listenner(&shell);
	// get_table(shell.ht);
	//TODO: REMOVE ALL THE BUCKET AND FREE THE HASHTABLE
	FREE(shell.ht);
	return (0);
}
