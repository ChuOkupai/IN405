#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int	main()
{
	pid_t	pid;
	int		n;
	
	srand(time(NULL));
	pid = fork();
	n = 0;
	printf("Mon PID est %d et celui de mon ", getpid());
	if (! pid)// child
	{
		printf("père est %d !\n", getppid());
		n = rand() % 50 + 1;
		printf("Nombre random = %d\n", n);
		return n;
	}
	else // father
	{
		wait(&n);
		printf("fils est %d !\n", pid);
		if (WIFEXITED(n))
			printf("Nombre random du fils = %d\n", WEXITSTATUS(n));
	}
	return 0;
}