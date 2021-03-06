include config.mk

OBJ=bin/frame.o bin/graphics.o bin/util.o

all: mkbin options klassychnya.exe

mkbin:
	@mkdir -p bin

options:
	@echo klassychnya.exe build options:
	@echo "CFLAGS  = ${CFLAGS}"
	@echo "LDFLAGS = ${LDFLAGS}"
	@echo "CC      = ${CC}"

bin/%.o: src/%.c
	@echo CC $<
	@${CC} -o $@ -c ${CFLAGS} $<

klassychnya.exe: ${OBJ}
	@echo CC -o $@
	@${CC} -static -o $@ ${OBJ} ${LDFLAGS}
	@echo $@ finished compiling.

clean:
	@echo cleaning
	@rm -f bin/*.o klassychnya.exe
