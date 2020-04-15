CC=gcc

CFLAGS=-c -Wall -Wextra

all: pdp11

pdp11: pdp.o main.o
	$(CC) pdp.o main.o -o a.out

pdp11.o: pdp11.c
	$(CC) $(CFLAGS) pdp.c

main.o: main.c
	$(CC) $(CFLAGS) main.c


clean:
	rm -rf *.o pdp11
