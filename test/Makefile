CC=g++ -std=c++20
CFLAGS=-c -Wall 
LDFLAGS=-L. -lgtest -llogicalElement

all: exe

exe: main.o
	$(CC) main.o $(LDFLAGS) -o exe

main.o:: main.cpp
	$(CC) $(CFLAGS) main.cpp	

clean:
	rm -f *.o *.a exe