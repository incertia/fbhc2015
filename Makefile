CC=gcc
CFLAGS=-Wall -pedantic -O3
TARGETS=swap nyr maze

all: $(TARGETS)

swap: swap.o
	$(CC) $(CFLAGS) -o swap swap.o

nyr: nyr.o
	$(CC) $(CFLAGS) -o nyr nyr.o

maze: maze.o
	$(CC) $(CFLAGS) -o maze maze.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

.PHONY: clean

clean:
	rm -rf *.o *.gch $(TARGETS)
