/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:18:43 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/19 00:36:33 by lkaba            ###   ########.fr       */
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
# include <limits.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <sys/wait.h>
# include "libft/libft.h"
# define QT 1u
# define DQT 2u
# define MINIMIZING 2u
# define LIGHT_RED "\033[1;31m"
# define NO_COLOUR "\033[0m"
# define PROMPT ft_putstr(LIGHT_RED"$> "NO_COLOUR)
# define TOK_BUFSIZE 7
# define _PATH_BSHELL "/bin"
# define _PATH_CSHELL "/bin/csh"
# define NUM_ARGS(...)IMPL(0, ##__VA_ARGS__, 13,12,11,10,9,8,7,6,5,4,3,2,1,0)
# define IMPL(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,N,...) N
# define NUM_TOKS(...) NUM_ARGS(__VA_ARGS__)
# define BUILTINS "echo cd env setenv unsetenv exit"

/*
**9: horizontal tab; 10: \n new line; 32: space; 34:"" d_quote; 35:# hash;
**39 = s_quote; 36:$ ampercent; 127: delete;
*/

// # define FILTERS 32, 8, 9, 34, 36, 39, 92, 0
# define SPCIDX	{['$'] = 1, ['#'] = 2, [34] = 2, [39] = 2}
# define KEY1 [9] = 1, [10] = 2, [27] = 3,
# define KEY2 [34] = 4, [39] = 5, [127] = 6
# define KEYMAP(...) {__VA_ARGS__}
# define SPCHAR	36, 35, 92
# define ONLYALPHA_NUM "Variable name must contain alphanumeric characters."
# define BAD_VAR "Variable name must begin with a letter."
# define NOPATH "A component of the pathname no longer exists."
# define NODIR "Can't change to home directory."
# define NOFDIR "No such file or directory."
# define NOSTR "String not in pwd."
# define MANY "Too many arguments."
# define FEW "Too few arguments."
// # define IS_SPACE(x) x >> 0 & 1 from snesei
// # define IS_QUOTE(x) x >> 1 & 1
volatile t_bool g_running;
volatile t_bool g_next_line;

typedef struct s_shell		t_shell;
typedef struct s_command	t_command;
typedef struct termios		t_termios;
typedef void 				(*const sig_ptr)(int);
typedef void				(*sc_fptr)(t_shell *, int *);

/*
** function pointer for key
*/
typedef ssize_t				(*wptr)(int, const void *, unsigned long);
typedef void				(*kptr)(t_shell *, char);

struct						s_command
{
	t_vector		*vec;
	int				status;
	pid_t			id;
	t_command		*next;
};
struct						s_shell
{
	t_command		*proc;
	t_hashtable		*ht;
	t_hashtable		*ex;
	t_memtrack		*mt;
	t_command		*cmd;
	char			spchar[UINT8_MAX];
	char			pwd[PATH_MAX];
	char			olpwd[PATH_MAX];
	t_vector		*path;
	t_dstr			*dstr;
	char 			isquote;
	t_dllnode		history;
	pid_t			parent_id;
	uint16_t		id;
	uint8_t			fptr_len;
	t_termios		old_t_attr;
	volatile t_bool is_readding;
};

void						parse_env(t_shell *s, char **env);
void						split_line(t_shell *s, t_vector *vec);
void						stdin_listenner(t_shell *s);
char						**get_table(t_hashtable *ht);
int8_t						get_index(char *cmd, char *builtins);
void						set_unbeffered(void);
void						signal_handler(void);
void						special_char_converter(t_shell *s, int32_t buf_idx);
int32_t						is_spchar(t_shell *s, sc_fptr *ddollard_fptr);
void						recycled_bin(t_shell *s);

/*
**builtin functions
*/
int						cmd_echo(t_shell *s, int argc, char **args);
int						cmd_cd(t_shell *s, int argc, char **args);
int						cmd_env(t_shell *s, int argc, char **args);
int						cmd_setenv(t_shell *s, int argc, char **args);
int						cmd_unsetenv(t_shell *s, int argc, char **args);
int						cmd_exit(t_shell *s, int argc, char **args);

/*
**Special charactere handler
*/
void						dollard_handler(t_shell *s, int *idx);
void						ddollard_handler(t_shell *s, int *idx);
void						hash_handler(t_shell *s, int *idx);
void						quote_handler(t_shell *s, int *idx);
void						backslash_handler(t_shell *s, int *idx);
void						whitespace_handler(t_shell *s, int *idx);
void						semicolon_handler(t_shell *s, int *idx);

/*
**keymap handler:each key pressed jump to a specific function
*/
void 						fn_other_key(t_shell *s, char c);
void 						fn_tab(t_shell *s, char c);
void 						fn_new_line(t_shell *s, char c);
void 						fn_delete(t_shell *s, char c);
void 						fn_dquote(t_shell *s, char c);
void 						fn_quote(t_shell *s, char c);
void 						fn_with_esc(t_shell *s, char c);


/*
**builtin function pointer each command return a specific index
**to call that function at the given index.
*/
static int					(* const g_fptr[])(t_shell *, int argc, char **) =
{
	cmd_echo,
	cmd_cd,
	cmd_env,
	cmd_setenv,
	cmd_unsetenv,
	cmd_exit
};

/*
**index initialization
**If you update spchar make sure to update the
**function pointer array in scpecial_char_converter
*/
void						index_table_init(char *table);

/*
**initialization for dooble quotes
**this will turn off all the all whitespaces and single quote
*/
void						index_table_dquote_init(char *table);

/*
**initialization for single quotes
**this will turn off all the all whitespaces and dooble quote
*/
void						index_table_quote_init(char *table);

const static char index_char[UINT8_MAX] =
{
	[9] = 1, [10] = 2, [27] = 3,
	[34] = 4, [39] = 4, [127] = 5
};

/*
**jumping table of all the keypressed by the user to determine
**the appropriate on each call. this will help us to avoid
**if else statement hell
*/
static  kptr const g_keys[UINT8_MAX] =
{
	fn_other_key,//0
	fn_tab,//9
	fn_new_line,//10
	fn_with_esc,//27
	fn_quote, //34 //39
	fn_delete//127
};

int						fd_num(char *device); //to remove later
#endif
