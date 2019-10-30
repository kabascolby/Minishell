/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:18:43 by lkaba             #+#    #+#             */
/*   Updated: 2019/10/28 20:46:43 by lkaba            ###   ########.fr       */
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
# define PROMPT ft_printf("$> ")
# define TOK_BUFSIZE 10
# define FILTER " \t\"\r\n\a"
# define _PATH_BSHELL "/bin"
# define _PATH_CSHELL "/bin/csh"
# define TOKENS "echo", "cd", "unsetenv", "env", "exit", "NULL"
# define FREE(p) do { free(p); p = NULL;} while(0)

typedef struct 	s_process	t_process;
typedef struct	s_shell	t_shell;

struct 	s_process
{
	// t_shell			*shell;
    char			**tokens;
	int				status;
	int				id;
};

struct	s_shell
{
	t_process		*proc;
	t_hashtable		*ht;
	t_hashtable		*ex;
	void			(*fptr[5])(t_shell *, char **);
	uint8_t				fptr_len;
};

void	parse_env(t_shell *s, char **env);
char	**split_line(char *line);
void	stdin_listenner(t_shell *);
char	**get_table(t_hashtable *ht);
int8_t	get_index(t_shell *, char *, ...);
void	cmd_env(t_shell *s, char **args);
void	cmd_exit(t_shell *s, char **args);
#endif
