CC=gcc
CFLAGS=-O3 -I $(pwd) -Wformat-overflow
DEPS = Kalashnikov.h

Kalashnikov: Kalashnikov.c
	$(CC) -o Kalashnikov Kalashnikov.c