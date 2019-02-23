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
# define PROMPT "$> "

typedef struct  s_shell
{
    char *str;
    char **buff;
}               t_shell;
#endif