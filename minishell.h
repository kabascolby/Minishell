/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:18:43 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/26 19:51:38 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <sys/stat.h>
# include <termios.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <sys/wait.h>
# include "libft/libft.h"
# define PROMPT ft_putstr("$> ")
# define TOK_BUFSIZE 2
# define _PATH_BSHELL "/bin"
# define _PATH_CSHELL "/bin/csh"
# define NUM_ARGS(...)IMPL(0, ##__VA_ARGS__, 13,12,11,10,9,8,7,6,5,4,3,2,1,0)
# define IMPL(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,N,...) N
# define NUM_TOKS(...) NUM_ARGS(__VA_ARGS__)
# define TOKENS "echo", "cd", "env", "setenv", "unsetenv", "exit"
# define WHITE { [' '] 1, ['\t'] 5,['\f']1, ['\n'] 3, ['\r'] 4 }
// # define SPCHAR2 ' '\\' '$' '\"' '#' ';' '\n'
/*
** 10: \n new line; 32: space; 34:"" d_quote; 35:# hash; 36:$ ampercent
*/

# define FILTERS 32, 8, 9, 34, 35, 36, 39, 92, 0
# define ONLYALPHA_NUM "Variable name must contain alphanumeric characters."
# define BAD_VAR "Variable name must begin with a letter."
# define NOPATH "A component of the pathname no longer exists."
# define NODIR "Can't change to home directory."
# define NOFDIR "no such file or directory."
# define NOSTR "string not in pwd"

typedef struct s_shell		t_shell;
typedef struct s_command	t_command;
// typedef struct s_tokens		t_tokens;
typedef struct termios		t_termios;
typedef void 				(*const sig_ptr)(int);

struct						s_command
{
	char			**tokens;
	int				status;
	pid_t			id;
	uint8_t			is_quote;
	uint8_t			is_space;
	uint8_t			is_backslash;
	t_command		*next;
};
struct						s_shell
{
	t_command		*proc;
	t_hashtable		*ht;
	t_hashtable		*ex;
	t_memtrack		*mt;
	char			*line;
	char			*filters;
	t_dllnode		history;
	pid_t			parent_id;
	uint16_t		id;
	uint8_t			fptr_len;
	t_termios		old_t_attr;
};

void						parse_env(t_shell *s, char **env);
char						**split_line(t_shell *s);
void						stdin_listenner(t_shell *s);
char						**get_table(t_hashtable *ht);
int8_t						get_index(t_shell *s, char *cmd, ...);
void						cmd_echo(t_shell *s, char **args);
void						cmd_cd(t_shell *s, char **args);
void						cmd_env(t_shell *s, char **args);
void						cmd_setenv(t_shell *s, char **args);
void						cmd_unsetenv(t_shell *s, char **args);
void						cmd_exit(t_shell *s, char **args);
void						set_unbeffered(void);
void						signal_handler(void);


static void					(* const g_fptr[])(t_shell *, char **) =
{
	cmd_echo,
	cmd_cd,
	cmd_env,
	cmd_setenv,
	cmd_unsetenv,
	cmd_exit
};

#endif
