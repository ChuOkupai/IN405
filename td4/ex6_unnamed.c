#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PIPE_PATH "/tmp/IN405_pipe"

int	main()
{
	char	buffer0[16];
	int		buffer1[2];
	int		fd;
	pid_t	child;

	if (mkfifo(PIPE_PATH, 0666) < 0 && errno != EEXIST)
	{
		perror("mkfifo error");
		return -1;
	}
	child = fork();
	if (child < 0)
		perror("fork error");
	else if (child)
	{
		fd = open(PIPE_PATH, O_RDONLY);
		read(fd, buffer0, sizeof(buffer0));
		read(fd, buffer1, sizeof(buffer1));
		close(fd);
		printf("Data: \"%s\", %d, %d\n", buffer0, buffer1[0], buffer1[1]);
		wait(NULL);
	}
	else // parent
	{
		buffer1[0] = 864;
		buffer1[1] = 7837;
		fd = open(PIPE_PATH, O_WRONLY);
		write(fd, "Hello, World!", sizeof(buffer0));
		write(fd, buffer1, sizeof(buffer1));
		close(fd);
	}
	return 0;
}
