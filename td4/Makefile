CC=gcc
CFLAGS=-Wall -Werror -Wextra

clean:
	rm -f *.out

ex%.out: ex%.c
	$(CC) $(CFLAGS) $< -o $@

ex1: ex1.out
	./$<

ex2: ex2.out
	./$<

ex3: ex3.out
	./$<

ex4: ex4.out
	./$< .

ex5: ex5.out
	./$<

ex6_named: ex6_named.out
	./$<

ex6_unnamed: ex6_unnamed.out
	./$<