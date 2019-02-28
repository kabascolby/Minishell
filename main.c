#include "minishell.h"

char **split_line(char *line)
{
	uint32_t	i;
	// char		*tok;
	char		**tokens;
	char		**tmp;
	uint32_t 	bufsize;

	i = -1;
	bufsize = TOK_BUFSIZE;
	MALLOC(tokens, bufsize * sizeof(char *));
	while ((tokens[++i] = ft_strtok_r(line, FILTER, &line)) != NULL)
	{
		if(i >= TOK_BUFSIZE)
		{
			MALLOC(tmp, (bufsize + TOK_BUFSIZE) * sizeof(char *));
			ft_memcpy((char **)tmp, (char **)tokens, bufsize);
			bufsize += TOK_BUFSIZE;
			FREE(tokens);
			tokens = tmp;
		}
	}
	tokens[i] = NULL;
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
	// while(1){
	// }
	// int i = 0;
	// while ((tab[i] = ft_strtok_r(argv[1], " *", &argv[1])) != NULL)
	// 	i++;
	// for (int i = 0; tab[i] && i < 8; i++)
	// 	printf("%s\n", tab[i]);


	return 0;
}