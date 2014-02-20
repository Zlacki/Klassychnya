PREFIX=/usr

INCS = -I. -I/usr/include -I/usr/local/include
LIBS = -L/usr/lib -L/usr/local/lib `sdl-config --libs` -lSDL_ttf

CFLAGS = -std=c99 -Wall -pedantic -O2 -ggdb3 `sdl-config --cflags` ${INCS}
LDFLAGS = -g ${LIBS}

CC = gcc
