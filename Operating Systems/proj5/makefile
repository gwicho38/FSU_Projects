#gcc -std=c99 -Wall -Wextra -D_XOPEN_SOURCE=700 -o trans trans.c -lrt

CC = gcc -std=c99
CFLAGS= -Wall -Wextra -D_XOPEN_SOURCE=700

all:  trans.x

trans.x: trans.c
	$(CC) $(CFLAGS) -o trans.x trans.c -lrt

