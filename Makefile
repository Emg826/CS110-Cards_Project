CFLAGS=-std=c99
CC=gcc

cards: main.c
	$(CC) $(CFLAGS) main.c -o cards

clean:
	rm -f cards *.o
