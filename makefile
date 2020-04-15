all: pdp11

pdp11: pdp.o main.o
        gcc pdp.o main.o -o a.out
pdp.o: pdp.c
        gcc -c -Wall -Wextra pdp.c
main.o: main.c
        gcc -c -Wall -Wextra main.c


clean:
	rm -rf *.o pdp11
