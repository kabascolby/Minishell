#include "minishell.h"

extern char **environ;

void stdin_listenner(void)
{
	char	*line;
	t_process	proc;

	PROMPT;
	line = NULL;
	ft_bzero((t_process *)&proc, sizeof(t_process));
	if (get_next_line(1, &line) > 0)
	{
		printf("line----------->%s\n",line);
		proc.tokens = split_line(line);
		 int p = 0;
		if (0 == (p = fork()))
		{
			printf("p1 --> %s |p2-> %s |p3--> %s\n", proc.tokens[0], proc.tokens[1], proc.tokens[2]);

			ft_printf("________________child_____________%d___%d\n", getpid(), p);
			if(-1 == execlp(proc.tokens[0], proc.tokens[1], proc.tokens[2], NULL))
				ft_putendl("invalide commmad");
		}
		else
		{
			wait(&p);
			ft_printf("________________parent________%d___%d\n", getpid(), p);
		}
		stdin_listenner();
	}
}

int main()
{
	t_shell	shell;

	ft_bzero((t_shell *)&shell, sizeof(t_shell));
	shell.ht = hashtable_init(INIT_HASHTABLE_SIZE);
	parse_env(&shell, environ);
	stdin_listenner();
	return (0);
}
