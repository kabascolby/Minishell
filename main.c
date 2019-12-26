/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 10:04:57 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 13:43:12 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **environ)
{
	t_shell		shell;
	t_dstr		dstr;

	(void)argc;
	(void)argv;
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
	get_history(&shell);
	stdin_listenner(&shell);
	restor_terminal(&shell);
	return (0);
}
