/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:18:43 by lkaba             #+#    #+#             */
/*   Updated: 2019/10/18 22:08:02 by lkaba            ###   ########.fr       */
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
# define FILTER " \"\t\r\n\a"

#define BAR_HELPER(a, ...) (void)(a, __VA_ARGS__)
#define UNUSED2(...) BAR_HELPER(__VA_ARGS__, 0)

// #define UNUSED2(...) (void)(__VA_ARGS__, throwaway)

# define FREE(p) \
do \
{ \
  free(p); \
  p = NULL; \
} \
while(0)


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
};

void	parse_env(t_shell *s, char **env);
char	**split_line(char *line);
void	stdin_listenner(void);

#endif
