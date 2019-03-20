#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	main()
{
	char	buffer0[16];
	int		buffer1[2];
	int		fd[2];
	pid_t	child;

	if (pipe(fd) < 0)
	{
		perror("pipe error");
		return -1;
	}
	child = fork();
	if (child < 0)
		perror("fork error");
	else if (child)
	{
		close(fd[1]); // 0: READ, 1: WRITE
		read(fd[0], buffer0, sizeof(buffer0));
		read(fd[0], buffer1, sizeof(buffer1));
		close(fd[0]);
		printf("Data: \"%s\", %d, %d\n", buffer0, buffer1[0], buffer1[1]);
		wait(NULL);
	}
	else // parent
	{
		buffer1[0] = 864;
		buffer1[1] = 7837;
		close(fd[0]);
		write(fd[1], "Hello, World!", sizeof(buffer0));
		write(fd[1], buffer1, sizeof(buffer1));
		close(fd[1]);
	}
	return 0;
}
