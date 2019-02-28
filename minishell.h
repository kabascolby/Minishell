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
# define PROMPT ft_printf("$> ")
#define TOK_BUFSIZE 64
#define FILTER " \"\t\r\n\a"

typedef struct  s_process
{
    char	**list_tokens;
	int		status;
	int		id;
}               t_process;
#endif