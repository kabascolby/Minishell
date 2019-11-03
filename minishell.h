/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:18:43 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/02 22:56:43 by lkaba            ###   ########.fr       */
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
# define TOKENS "echo", "cd", "env", "setenv", "unsetenv", "exit", "NULL"
# define FREE(p) do { free(p); p = NULL;} while(0)
# define ONLYALPHA_NUM "Variable name must contain alphanumeric characters."
# define BAD_VAR "Variable name must begin with a letter."

typedef struct	s_shell		t_shell;
typedef struct 	s_process	t_process;
struct 	s_process
{
	// t_shell			*shell;
    char			**tokens;
	u_int8_t		status;
	uint16_t		id;
	t_process		*next;
};
struct	s_shell
{
	t_process		*proc;
	t_hashtable		*ht;
	t_hashtable		*ex;
	void			(*fptr[NUM_TOKS(TOKENS) - 1])(t_shell *, char **);
	char			*line;
	uint16_t		id;
	uint8_t			fptr_len;
};

extern char **environ;

void	parse_env(t_shell *s);
char	**split_line(char *line);
void	stdin_listenner(t_shell *);
char	**get_table(t_hashtable *ht);
int8_t	get_index(t_shell *, char *, ...);
void 	cmd_echo(t_shell *s, char **args);
void	cmd_cd(t_shell *s, char **args);
void	cmd_env(t_shell *s, char **args);
void	cmd_setenv(t_shell *s, char **args);
void	cmd_exit(t_shell *s, char **args);
void	cmd_unsetenv(t_shell *s, char **args);
#endif
