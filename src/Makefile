CC=gcc
CPP=g++
CFLAGS=-Wall

default: aqueduct

debug: CFLAGS += -g -D DEBUG
debug: aqueduct

aqueduct: main.cpp bfm.o
	@$(CPP) $(CFLAGS) -o $@ $^

%.0: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@rm -f aqueduct *.o
