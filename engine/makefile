CXX	= g++
CFLAGS 	= -g -Wall -std=c++17 -Os
TARGET	= enigma
SOURCES = src/*.cc src/objects/*.cc
LIBS	= -lglfw -lGLEW -lGLU -lGL
INCL	= -I src -I src/vendor/glm -I src/vendor/glm/gtc -I src/objects
DESTDIR = /usr/local/bin

all: ${TARGET}

${TARGET}: ${SOURCES}
	${CXX} ${CFLAGS} -o ${TARGET} ${INCL} ${SOURCES} ${LIBS}

clean:
	rm ${TARGET}

install: all
	mkdir -p ${DESTDIR}
	cp -f ${TARGET} ${DESTDIR}
	chmod +x ${DESTDIR}/${TARGET}

debug: all
	gdb ${TARGET}

run: all
	./${TARGET}
