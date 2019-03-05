#include "minishell.h"

char **split_line(char *line)
{
	char		**tokens;
	char		**tmp;
	uint8_t 	bufsize;
	uint16_t	i;

	bufsize = TOK_BUFSIZE;
	MALLOC(tokens, bufsize);
	i = -1;
	while ((tokens[++i] = ft_strtok_r(line, FILTER, &line)) != NULL)
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
		printf("%s\n",line);
		proc.list_tokens = split_line(line);
		//  int p = 0;
		// if (0 == (p = fork()))
		// {
		// 	if(-1 == execlp(proc.list_tokens[0], proc.list_tokens[1], proc.list_tokens[2], NULL))
		// 		ft_putendl("invalide commmad");
		// 	// ft_printf("________________child_____________%d___%d\n", getpid(), p);
		// }
		// else
		// {
		// 	wait(&p);
		// 	ft_printf("________________parent________%d___%d\n", getpid(), p);
		// }
		stdin_listenner();
	}
}

void parse_env(t_shell *shell, char **env)
{
	// get_env//to implemented later
	uint16_t	len;
	uint16_t	i;

	len = 0;
	while(env[++len])
		;
	shell->env = (char **)malloc(sizeof(char *) * (len + 1));
	i = -1;
	while(env[++i])
		shell->env[i] = ft_strdup(env[i]);
	shell->env[i + 1] = NULL;
}

int main(int argc, char **argv, char **env)
{
	t_shell	shell;
	UNUSED(argc);
	UNUSED(argv);
	ft_bzero((t_shell *)&shell, sizeof(t_shell));
	parse_env(&shell, env);
	stdin_listenner();
	return (0);
}
	// int p;
	// if (0 == (p = fork()))
	// 	ft_printf("________________child_____________%d___%d\n", getpid(), p);
	// else
	// 	ft_printf("________________parent________%d___%d\n", getpid(), p);