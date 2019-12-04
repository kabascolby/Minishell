/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 10:04:57 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/02 20:19:04 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **environ)
{
	t_shell		shell;
	t_dstr		dstr;

	ft_bzero((t_shell *)&shell, sizeof(t_shell));
	shell.proc = MALLOC(sizeof(t_command));
	UNUSED(argc, argv);
	dstr_init(&dstr);
	shell.dstr = &dstr;
	tcgetattr(STDIN_FILENO, &shell.old_t_attr);
	shell.parent_id = getpid();
	set_unbeffered();
	shell.ht = hashtable_init(INIT_HASHTABLE_SIZE);
	// signal_handler();
	shell.mt = memtracker_init(300);
	parse_env(&shell, environ - 1);
	shell.fptr_len = NUM_TOKS(TOKENS);
	stdin_listenner(&shell);
	FREE(shell.ht);
	return (0);
}
	//TODO: FREE HT  and ht buckets AND MT
