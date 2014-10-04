PREFIX=/usr

INCS = -I. -I/usr/x86_64-w64-mingw32/include
LIBS = -L/usr/x86_64-w64-mingw32/lib `x86_64-w64-mingw32-sdl2-config --libs` -lmingw32 -lSDL2main -lSDL2 -mwindows -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -static-libgcc -lSDL2_ttf -lfreetype -lbz2

CFLAGS = -std=c99 -Wall -pedantic -O2 -ggdb3 `x86_64-w64-mingw32-sdl2-config --cflags` ${INCS}
LDFLAGS = -g ${LIBS}

CC = x86_64-w64-mingw32-gcc
