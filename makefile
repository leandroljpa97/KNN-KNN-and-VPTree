CC=gcc
CFLAGS= -O2 -I. -Wall -lm -std=gnu11
DEPS = utils.h classification.h
OBJ = utils.c classification.c main.c

default: main

all: main

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o main