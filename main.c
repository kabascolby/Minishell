#include "minishell.h"

char **split_line(char *line)
{
	uint32_t	i;
	char		**tokens;
	char		**tmp;
	uint32_t 	bufsize;

	bufsize = TOK_BUFSIZE;
	MALLOC(tokens, bufsize);
	i = -1;
	while ((tokens[i] = ft_strtok_r(line, FILTER, &line)) != NULL)
	{	
		if(i + 1 >= TOK_BUFSIZE)
		{
			MALLOC(tmp, bufsize + TOK_BUFSIZE);
			ft_memcpy((char **)tmp, (char **)tokens, bufsize * sizeof(char *));
			bufsize += TOK_BUFSIZE;
			FREE(tokens);
			tokens = tmp;
			tmp = NULL;
		}
	}
	tokens[++i] = NULL;
			ft_putstr("________________Here_____________\n");
	for (int i = 0; tokens[i]; i++)
		printf("%s\n", tokens[i]);
	return tokens;	
}

void stdin_listenner(void)
{
	char	*line;
	t_process	proc;
	
	PROMPT;
	line = NULL;
	ft_bzero((t_process *)&proc, sizeof(t_process));
	if (get_next_line(1, &line) > 0)
	{
		proc.list_tokens = split_line(line);
		stdin_listenner();
	}
}


int main(int argc, char **argv)
{
	UNUSED(argc);
	UNUSED(argv);
	stdin_listenner();
	return (0);
}