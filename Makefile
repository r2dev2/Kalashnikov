CC=gcc
CFLAGS=-O3 -I $(pwd)
DEPS = Kalashnikov.h

Kalashnikov: Kalashnikov.c
	$(CC) -o Kalashnikov Kalashnikov.c