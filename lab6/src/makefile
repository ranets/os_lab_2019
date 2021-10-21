CC=gcc
CFLAGS=-std=c99 -w -pthread

all : client.o server.o

client.o : client.c
	$(CC) -o $@ $^ $(CFLAGS)

server.o : server.c
	$(CC) -o $@ $^ $(CFLAGS)