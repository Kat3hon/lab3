CC=g++ -std=c++20
CFLAGS=-c -Wall -DN=5
LDFLAGS=-L. -llogicalElement

all: exe

exe: dialog.o help.o main.o
	$(CC) dialog.o main.o help.o $(LDFLAGS) -o exe

main.o:: main.cpp
	$(CC) $(CFLAGS) main.cpp	

dialog.o: dialog.cpp
	$(CC) $(CFLAGS) dialog.cpp

help.o: help.cpp
	$(CC) $(CFLAGS) help.cpp	

clean:
	rm -f *.o *.a exe