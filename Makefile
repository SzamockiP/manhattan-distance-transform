CFLAGS = -Wall -Wextra -Wpedantic -Werror

program: main.o
	gcc -std=c11 -O2 $(CFLAGS) main.o  -o program -lm

main.o: main.c
	gcc -std=c11 -O2 $(CFLAGS) -c main.c -o main.o

clean:
	rm -f *.o program


