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
# define FILTER " \"\t\r\n\a"

typedef struct 	s_process	t_process;
typedef struct	s_shell	t_shell;

struct 	s_process
{
	// t_shell			*shell;
    char			**list_tokens;
	int				status;
	int				id;
};

struct	s_shell
{
	t_process		*proc;
	char			**env;
};	

#endif