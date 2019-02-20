CC=gcc
CFLAGS=-O3 -Wall -Werror -Wextra

clean:
	rm -f *.o *.out

stat.o: stat.c stat.h
	$(CC) $(CFLAGS) -c $< -o $@ -I./include

ls.out: ls.c stat.o stat.h
	$(CC) $(CFLAGS) $< -o $@ stat.o