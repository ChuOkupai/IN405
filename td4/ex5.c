#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	main()
{
	pid_t pid;
	
	if (! (pid = fork())) // child
	{
		for (char c = '1'; c < '6'; c++)
		{
			sleep(1);
			putchar(c);
			putchar('\n');
		}
		return 0;
	}
	else // parent
	{
		sleep(3);
		kill(pid, SIGSTOP);
		sleep(5);
		kill(pid, SIGCONT);
		wait(NULL);
	}
	return 0;
}