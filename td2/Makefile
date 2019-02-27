CC=gcc
CFLAGS=
LDFLAGS=-L. -lsef

clean:
	rm -f *.out *.o

se_fichier.o: se_fichier.c se_fichier.h
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

libsef.a: se_fichier.o
	ar rcs $@ $<

main-opt.out: main-opt.c se_fichier.h libsef.a
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

main.out: main.c se_fichier.h libsef.a
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)