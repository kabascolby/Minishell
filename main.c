#include "minishell.h"

int main(int argc, char* argv[])
{
	char buf[MaxCommandLine];
	int n, paramNumber;
	int commandType;
	char* params[4];
	printPrompt();
	while ((n=read(STDIN_FILENO, buf, MaxCommandLine))>0)
	{
		buf[n]='\0';
		commandType=parseCommand(buf, params, &paramNumber);
		if (commandType==-1)
		{
			printf("illegal command\n%s");
		}
		else
		{
			commandArray[commandType](params, paramNumber);			
		}
		printPrompt();
	}
	return 0;
}
