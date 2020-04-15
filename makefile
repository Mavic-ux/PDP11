CC=gcc

CFLAGS=-c -Wall -Wextra

all: pdp11

pdp11: pdp.o pdprun.o main.o
	$(CC) pdp.o pdprun.o main.o -o a.out

pdp.o: pdp.c
	$(CC) $(CFLAGS) pdp.c

pdprun.o: pdprun.c
	$(CC) $(CFLAGS) pdprun.c

main.o: main.c
	$(CC) $(CFLAGS) main.c 

clean:
	rm -rf *.o pdp11
