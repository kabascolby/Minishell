/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:18:43 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/26 11:14:40 by lkaba            ###   ########.fr       */
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
# define LIGHT_RED "\033[1;31m"
# define LIGHT_GREEN "\033[1;32m"
# define NO_COLOUR "\033[0m"

/*
**Error messages
*/
# define BUILTINS "echo cd env setenv unsetenv exit"
# define ONLYALPHA_NUM "Variable name must contain alphanumeric characters."
# define BAD_VAR "Variable name must begin with a letter."
# define NOPATH "A component of the pathname no longer exists."
# define NODIR "Can't change to home directory."
# define NOFDIR "No such file or directory."
# define NOSTR "String not in pwd."
# define MANY "Too many arguments."
# define FEW "Too few arguments."

/*
**Gobal variables for signals
*/
volatile t_bool				g_running;
volatile t_bool				g_next_line;

typedef struct s_shell		t_shell;
typedef struct s_command	t_command;
typedef struct termios		t_termios;
typedef void				(*t_sc_fptr)(t_shell *, int *);

/*
** function pointer for key
*/
typedef void				(*t_kptr)(t_shell *, char);

struct						s_command
{
	t_vector		*vec;
	pid_t			child_pid;
	t_command		*next;
};

/*
**Main struct
*/
struct						s_shell
{
	t_command		*proc;
	t_hashtable		*ht;
	t_memtrack		*mt;
	t_command		*cmd;
	t_hashtable		*path;
	int				status;
	uint32_t		pos;
	char			spchar[UINT8_MAX];
	char			pwd[PATH_MAX];
	char			olpwd[PATH_MAX];
	t_dstr			*dstr;
	char			isquote;
	t_dllnode		*history;
	t_dllnode		*cur_hist;
	pid_t			parent_id;
	uint16_t		id;
	uint8_t			fptr_len;
	t_termios		old_t_attr;
	t_bool			is_readding;
};

/*
**Parsing functions
*/
void						parse_env(t_shell *s, char **env);
void						parse_executable(t_shell *s);
void						special_char_converter(t_shell *s, int32_t buf_idx);
void						stdin_listenner(t_shell *s);
void						split_line(t_shell *s, t_vector *vec);

/*
**utility functions
*/
char						**get_table(t_hashtable *ht);
int8_t						get_index(char *cmd, char *builtins);
void						set_unbeffered(void);
void						signal_handler(void);
void						display_prompt(t_shell *s);
int32_t						is_spchar(t_shell *s, t_sc_fptr *ddollard_fptr);
void						recycled_bin(t_shell *s);
t_vector					*hastable_keys(t_hashtable *ht, t_vector **keys);
void						restor_terminal(t_shell *s);

/*
**builtin functions
*/
int							cmd_echo(t_shell *s, int argc, char **args);
int							cmd_cd(t_shell *s, int argc, char **args);
int							cmd_env(t_shell *s, int argc, char **args);
int							cmd_setenv(t_shell *s, int argc, char **args);
int							cmd_unsetenv(t_shell *s, int argc, char **args);
int							cmd_exit(t_shell *s, int argc, char **args);

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
void						backslash_tilde(t_shell *s, int *idx);
/*
**keymap handler:each key pressed jump to a specific function
*/
void						fn_other_key(t_shell *s, char c);
void						fn_tab(t_shell *s, char c);
void						fn_new_line(t_shell *s, char c);
void						fn_delete(t_shell *s, char c);
void						fn_dquote(t_shell *s, char c);
void						fn_quote(t_shell *s, char c);
void						fn_with_esc(t_shell *s, char c);

/*
**history
*/
t_bool						set_history(char *data);
t_bool						get_history(t_shell *s);

/*
**builtin function pointer each command return a specific index
**to call that function at the given index.
*/
static int					(*const g_fptr[])(t_shell *, int argc, char **) =
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

const static char			g_idx_char[UINT8_MAX] =
{
	[9] = 1,
	[10] = 2,
	[27] = 3,
	[34] = 4,
	[39] = 4,
	[127] = 5
};

/*
**jumping table of all the keypressed by the user to determine
**the appropriate on each call. this will help us to avoid
**if else statement hell
*/
static t_kptr const			g_keys[] =
{
	fn_other_key,
	fn_tab,
	fn_new_line,
	fn_with_esc,
	fn_quote,
	fn_delete
};
#endif
