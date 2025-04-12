CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -Werror

program: main.o
	gcc $(CFLAGS) main.o  -o program -lm

main.o: main.c
	gcc $(CFLAGS) -c main.c -o main.o

clean:
	rm -f *.o program


