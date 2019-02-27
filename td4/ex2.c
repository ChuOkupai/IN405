#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	main()
{
	int i;
	
	for (i = 0; i < 10; i++)
	{
		if (! fork())
		{
			srand(getpid());
			sleep(rand() % 10 + 1);
			printf("PID: %d\n", getpid());
			return 0;
		}
	}
	for (i = 0; i < 10; i++)
		printf("%d: processus terminé !\n", wait(NULL));
	return 0;
}