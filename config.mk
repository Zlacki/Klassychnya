PREFIX=/usr

INCS = -I. -I/usr/include -I/usr/local/include
LIBS = -L/usr/lib -L/usr/local/lib -lSDL

CFLAGS = -std=c99 -Wall -pedantic -O2 -D_BSD_SOURCE -ggdb3 ${INCS}
LDFLAGS = -g ${LIBS}

CC = gcc
