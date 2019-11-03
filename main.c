/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 10:04:57 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/02 22:42:32 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

int main()
{
	t_shell		shell;

	ft_bzero((t_shell *)&shell, sizeof(t_shell));
	shell.ht = hashtable_init(INIT_HASHTABLE_SIZE);
	parse_env(&shell);
	shell.fptr_len = NUM_TOKS(TOKENS) - 1;
	shell.fptr[0] = cmd_echo;
	shell.fptr[1] = cmd_cd;
	shell.fptr[2] = cmd_env;
	shell.fptr[3] = cmd_setenv;
	shell.fptr[4] = cmd_unsetenv;
	shell.fptr[5] = cmd_exit;
	stdin_listenner(&shell);
	FREE(shell.ht);
	return (0);
}
	// shell.fptr = {cmd_echo, cmd_cd, cmd_unsetenv, cmd_env,cmd_setenv, cmd_exit};
	//TODO: REMOVE ALL THE BUCKET AND FREE THE HASHTABLE
