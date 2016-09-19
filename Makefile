CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG) -lncurses
OBJS = hexc.o

all: hexc

hexc: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o hexc
	
hexc.o: hexc.cpp hexc.hpp
	$(CC) $(CFLAGS) hexc.cpp
	
clean:
	rm *.o hexc

