CC=gcc
CFLAGS=  -I. -Wall -lm -std=gnu11
DEPS = utils.h classification.h
OBJ = utils.c classificationKNN.c main.c

default: main

all: main

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o main