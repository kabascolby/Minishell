/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 10:04:57 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/20 16:34:14 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	recycled_bin(t_shell *s)
{
	t_command  *proc;
	dstr_free(s->dstr);
	ft_mtdestroy(s->mt);
	hashtable_destroy(&s->ht);
	while(s->proc)
	{
		proc = s->proc;
		s->proc = s->proc->next;
		if(proc->vec)
			vector_free(&proc->vec);
		free(proc);
	}
	ft_putendl("exit");
}

int		main(int argc, char **argv, char **environ)
{
	t_shell		shell;
	t_dstr		dstr;

	UNUSED(argc, argv);
	ft_bzero((t_shell *)&shell, sizeof(t_shell));
	dstr_init(&dstr);
	shell.dstr = &dstr;
	tcgetattr(STDIN_FILENO, &shell.old_t_attr);
	shell.parent_id = getpid();
	set_unbeffered();
	shell.ht = hashtable_init(INIT_HASHTABLE_SIZE);
	signal_handler();
	shell.mt = memtracker_init(300);
	parse_env(&shell, environ - 1);
	parse_executable(&shell);
	getcwd(shell.pwd, PATH_MAX);
	getcwd(shell.olpwd, PATH_MAX);
	shell.fptr_len = sizeof(g_fptr) / sizeof(*g_fptr);
	stdin_listenner(&shell);
	return (0);
}
	//TODO: FREE HT  and ht buckets AND MT
