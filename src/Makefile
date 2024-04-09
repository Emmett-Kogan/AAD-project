CC=gcc
CPP=g++
CFLAGS=-Wall

default: main

debug: CFLAGS += -g
debug: main

main: main.c bfm.o
	@$(CC) $(CFLAGS) -o $@ $^

%.0: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@rm -f main *.o
