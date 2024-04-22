CC=gcc
CPP=g++
CFLAGS=-Wall

default: aqueduct

debug: CFLAGS += -g -D DEBUG
debug: aqueduct

big: CFLAGS += -g -DDEBUG -DBIG
big: aqueduct

aqueduct: main.cpp lib/bfm.o
	@$(CPP) $(CFLAGS) -o $@ $^

lib/%.o: lib/%.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@rm -f aqueduct lib/*.o
