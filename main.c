/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 10:04:57 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/25 11:20:28 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **environ)
{
	t_shell		shell;

	ft_bzero((t_shell *)&shell, sizeof(t_shell));
	UNUSED(argc, argv);
	tcgetattr(STDIN_FILENO, &shell.old_t_attr);
	shell.parent_id = getpid();
	set_unbeffered();
	// signal_handler();
	shell.ht = hashtable_init(INIT_HASHTABLE_SIZE);
	shell.mt = memtracker_init(300);
	parse_env(&shell, environ - 1);
	shell.fptr_len = NUM_TOKS(TOKENS);
	stdin_listenner(&shell);
	FREE(shell.ht);
	return (0);
}
	// shell.fptr = {cmd_echo, cmd_cd, cmd_unsetenv, cmd_env,cmd_setenv, cmd_exit};
	//TODO: FREE HT  and ht buckets AND MT
