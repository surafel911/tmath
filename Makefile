CC = clang
CFLAGS = -m64 -Wall -Werror -std=c99
BINARY = tmath
INCDIR = -I include/ -I /usr/include/
LIBDIR = -L /usr/lib/
LIBRARIES = -lm
TESTS = 
SOURCES = src/*.c

ifeq ($(OS),Windows_NT)
 BINARY += .exe
endif

all: debug

debug:
	$(CC) -g $(CFLAGS) $(INCDIR) $(LIBDIR) $(SOURCES) $(LIBRARIES) \
		-o bin/$(BINARY)

release:
	$(CC) -O3 $(CFLAGS) $(INCDIR) $(LIBDIR) $(SOURCES) $(LIBRARIES) \
		-o bin/$(BINARY)
