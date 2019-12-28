CC=gcc
CFLAGS= -O2 -I. -Wall -std=gnu11
DEPS = utils.h
OBJ = utils.c main.c

default: main

all: main

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o main