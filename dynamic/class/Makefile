CC=g++ -std=c++20
CFLAGS=-c -Wall
LDFLAGS=

liblogicalElement.a: class_functions.o
	ar rc liblogicalElement.a class_functions.o
	ranlib liblogicalElement.a
	cp logicalElement.h ~/c++/lab3/dynamic/main
	cp liblogicalElement.a ~/c++/lab3/dynamic/main
	cp logicalElement.h ~/c++/lab3/dynamic/test
	cp liblogicalElement.a ~/c++/lab3/dynamic/test

class_functions.o: class_functions.cpp logicalElement.h
	$(CC) $(CFLAGS) class_functions.cpp 

clean:
	rm -f *.o *.a exe