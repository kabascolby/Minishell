/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 10:04:57 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/15 15:08:12 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **environ)
{
	t_shell		shell;

	ft_bzero((t_shell *)&shell, sizeof(t_shell));
	UNUSED(argc, argv);
	tcgetattr(STDIN_FILENO, &shell.old_t_attr);
	set_unbeffered();
	// signal_handler();
	shell.ht = hashtable_init(INIT_HASHTABLE_SIZE);
	parse_env(&shell, environ - 1);
	shell.fptr_len = NUM_TOKS(TOKENS);
	stdin_listenner(&shell);
	FREE(shell.ht);
	return (0);
}
	// shell.fptr = {cmd_echo, cmd_cd, cmd_unsetenv, cmd_env,cmd_setenv, cmd_exit};
	//TODO: REMOVE ALL THE BUCKET AND FREE THE HASHTABLE
