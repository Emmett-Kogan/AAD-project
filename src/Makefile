CC=gcc
CPP=g++
CFLAGS=-Wall

default: aqueduct

debug: CFLAGS += -g -D DEBUG
debug: aqueduct

aqueduct: main.cpp lib/bfm.o
	@$(CPP) $(CFLAGS) -o $@ $^

lib/%.0: lib/%.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@rm -f aqueduct *.o
