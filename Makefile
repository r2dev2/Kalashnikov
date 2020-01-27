CC=gcc
CFLAGS=-O3 -I $(pwd) -Wformat-overflow=0
DEPS = Kalashnikov.h

Kalashnikov: src/Kalashnikov.c
	$(CC) -o bin/Kalashnikov src/Kalashnikov.c