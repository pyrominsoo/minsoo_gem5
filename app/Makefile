CC=gcc
CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local
SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
TARGETS=$(patsubst %.c,%,$(SOURCES))

# The Target Build
all: $(TARGETS)


arm: CC=arm-linux-gnueabihf-gcc
arm: all

dev: CFLAGS=-g -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGETS): build $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)
	mv $@ build/

build:
	@mkdir -p build
	@mkdir -p bin

# The Cleaner
clean:
	rm -rf build $(OBJECTS)

# The Checker
check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true

