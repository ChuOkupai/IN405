#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

void*	hello(void *empty)
{
	(void)empty;
	puts("Hello World!");
	return NULL;
}

void*	random1(void *n)
{
	if (! n)
		return NULL;
	printf("n1 = %d\n", *(int*)n);
	return NULL;
}

void*	random2(void *n)
{
	if (! n)
		return NULL;
	*(int*)n = rand();
	printf("n2 = %d\n", *(int*)n);
	return NULL;
}

void*	random3(void *t)
{
	if (! t)
		return NULL;
	int i, s = 0;
	for (i = 0; i < 5; i++)
		s += ((int*)t)[i];
	printf("sum = %d\n", s);
	return NULL;
}

void*	random4(void *t)
{
	if (! t || ((int*)t)[0] < 1)
		return NULL;
	int s = 0;
	while (((int*)t)[0]-- > 0)
		s += ((int*)t)[((int*)t)[0]];
	printf("sum = %d\n", s);
	return NULL;
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		return -1;
	int			i, n, n1, n2, tab1[5], *tab2;
	pthread_t	thread[5];
	
	n = atoi(argv[1]);
	if (n < 1)
		return -2;
	srand(getpid());
	n1 = rand();
	for (i = 0; i < 5; i++)
		tab1[i] = rand() % 429496729;
	tab2 = (int*)malloc(sizeof(int) * (n + 1));
	if (! tab2)
		return -1;
	tab2[0] = n;
	for (i = 1; i < n + 1; i++)
		tab2[i] = rand() % 2;
	pthread_create(&thread[0], NULL, hello, NULL);
	pthread_create(&thread[1], NULL, random1, &n1);
	pthread_create(&thread[2], NULL, random2, &n2);
	pthread_create(&thread[3], NULL, random3, tab1);
	pthread_create(&thread[4], NULL, random4, tab2);
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_join(thread[2], NULL);
	printf("n2 = %d\n", n2);
	pthread_join(thread[3], NULL);
	pthread_join(thread[4], NULL);
	free(tab2);
	return 0;
}
