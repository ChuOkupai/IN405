#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

char*	catarg(char *arg)
{
	char *dst;

	dst = (char*)malloc(7 + strlen(arg));
	if (! dst)
		exit(EXIT_FAILURE);
	dst[0] = '\0';
	strcat(dst, "ls -R ");
	strcat(dst, arg);
	return dst; 
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		exit(EXIT_FAILURE);
	char		*buf;
	struct tms	t;
	double		dt;
	
	buf = catarg(argv[1]);
	if (system(buf))
		exit(EXIT_FAILURE);
	times(&t);	
	dt = (double)(t.tms_cutime  + t.tms_cstime) / sysconf(_SC_CLK_TCK);
	printf("exec time: %lf\n", dt);
	free(buf);
	return 0;
}