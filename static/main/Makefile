CC=g++ -std=c++20
CFLAGS=-c -Wall
LDFLAGS=-L. -llogicalElement

all: exe

exe: clamps_processing.o board.o help.o main.o
	$(CC) clamps_processing.o board.o main.o help.o $(LDFLAGS) -o exe

main.o:: main.cpp
	$(CC) $(CFLAGS) main.cpp	

clamps_processing.o: clamps_processing.cpp
	$(CC) $(CFLAGS) clamps_processing.cpp

board.o: board.cpp 
	$(CC) $(CFLAGS) board.cpp

help.o: help.cpp
	$(CC) $(CFLAGS) help.cpp	

clean:
	rm -f *.o *.a exe