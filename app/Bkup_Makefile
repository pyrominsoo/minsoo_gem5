CC = gcc
ARM_CC = arm-linux-gnueabihf-gcc
CFLAGS= -Wall -g -static -DNDEBUG
SRCS = sieve_of_erato.c
#OBJS = $(EX1_SRCS:.c=.o)
NATIVE_PATH = native
ARM_LINUX_PATH = arm
TARGET = sieve_arm sieve

all: $(TARGET)

sieve: $(SRCS)
	$(CC) $(CFLAGS) -o $(NATIVE_PATH)/$@ $^

sieve_arm : $(SRCS)
	$(ARM_CC) $(CFLAGS) -o $(ARM_LINUX_PATH)/$@ $^

clean:
	rm -f *.o $(NATIVE_PATH)/* $(ARM_LINUX_PATH)/*
