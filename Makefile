CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2

all: artemis

artemis: main.c artemis.c listas.c validaciones.c artemis.h listas.h validaciones.h
	$(CC) $(CFLAGS) main.c artemis.c listas.c validaciones.c -o artemis -lm

clean:
	rm -f artemis

