CFLAGS = -Wall -g

SOURCE=$(wildcard src/*.c)

BIN=$(SOURCE:src/%.c=bin/%)

all:$(BIN)

bin/%:src/%.c
	@mkdir -p bin
	gcc $<  $(CFLAGS) -o $@

clean:
	rm -rf bin

.PHONY:clean all
