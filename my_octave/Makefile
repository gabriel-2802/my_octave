#copyright Carauleanu Valentin Gabriel 311CA

CC=gcc
CFLAGS=-Wall -Wextra -std=c99

build:
	$(CC) $(CFLAGS) my_octave.c dynamic_alloc.c numeric_functions.c commands.c strassen.c -o my_octave

clean:
	rm -f my_octave

.PHONY: pack clean