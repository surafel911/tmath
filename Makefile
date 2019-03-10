CC = clang
CFLAGS = -m64 -Wall -Werror -std=c99
BINARY = tmath
LIBBINARY = libtmath
INCDIR = -I include/ -I /usr/include/
LIBDIR = -L /usr/lib/
LIBRARIES = -lm
TESTS = test/*.c
SOURCES = src/*.c

ifeq ($(OS),Windows_NT)
 BINARY =  $(strip $(BINARY)).exe
 LIBBINARY := $(strip $(LIBBINARY)).dll
else
 LIBBINARY := $(strip $(LIBBINARY)).so
endif

all: debug

debug:
	$(CC) -g $(CFLAGS) $(INCDIR) $(LIBDIR) $(SOURCES) $(LIBRARIES) \
		$(TESTS) -o bin/$(BINARY)

release:
	$(CC) -O3 --shared $(CFLAGS) $(INCDIR) $(LIBDIR) $(SOURCES) $(LIBRARIES) \
		-o bin/$(LIBBINARY)

ifneq ($(OS),Windows_NT)
install: release
	$(shell sudo mv bin/$(LIBBINARY).* /usr/lib/)
endif
