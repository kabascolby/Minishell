/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:18:43 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/03 21:33:43 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/stat.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <sys/wait.h>
# define PROMPT ft_putstr("$> ")
# define TOK_BUFSIZE 10
# define FILTER " \\\t\"\r\n\a"
# define _PATH_BSHELL "/bin"
# define _PATH_CSHELL "/bin/csh"
# define NUM_ARGS(...)IMPL(0, ##__VA_ARGS__, 13,12,11,10,9,8,7,6,5,4,3,2,1,0)
# define IMPL(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,N,...) N
# define NUM_TOKS(...) NUM_ARGS(__VA_ARGS__)
# define TOKENS "echo", "cd", "env", "setenv", "unsetenv", "exit"
# define FREE(p) do { free(p); p = NULL;} while(0)
# define ONLYALPHA_NUM "Variable name must contain alphanumeric characters."
# define BAD_VAR "Variable name must begin with a letter."
# define NOPATH "A component of the pathname no longer exists."

typedef struct s_shell		t_shell;
typedef struct s_process	t_process;
struct						s_process
{
	char			**tokens;
	u_int8_t		status;
	pid_t			id;
	t_process		*next;
};
struct						s_shell
{
	t_process		*proc;
	t_hashtable		*ht;
	t_hashtable		*ex;
	char			*line;
	uint16_t		id;
	uint8_t			fptr_len;
};

void						parse_env(t_shell *s, char **env);
char						**split_line(char *line);
void						stdin_listenner(t_shell *s);
char						**get_table(t_hashtable *ht);
int8_t						get_index(t_shell *s, char *cmd, ...);
void						cmd_echo(t_shell *s, char **args);
void						cmd_cd(t_shell *s, char **args);
void						cmd_env(t_shell *s, char **args);
void						cmd_setenv(t_shell *s, char **args);
void						cmd_unsetenv(t_shell *s, char **args);
void						cmd_exit(t_shell *s, char **args);

static void					(*g_fptr[])(t_shell *, char **) =
{
	cmd_echo,
	cmd_cd,
	cmd_env,
	cmd_setenv,
	cmd_unsetenv,
	cmd_exit
};
#endif
