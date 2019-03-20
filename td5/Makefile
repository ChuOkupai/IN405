CC=gcc
CFLAGS=-Wall -Werror -Wextra
LDFLAGS=-lpthread

clean:
	rm -f *.out

ex%.out: ex%.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

ex1: ex1.out
	./$< 42