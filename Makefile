all: simpleOrderBook

simpleOrderBook: Parser.o main.o
	g++ Parser.o main.o -o simpleOrderBook
	rm -rf *.o

main.o: main.cpp
	g++ -std=c++17 -Wall -pedantic -c main.cpp

Parser.o: Parser.cpp Parser.h
	g++ -std=c++17 -Wall -pedantic -c Parser.cpp

clean:
	rm -rf *.o gzzip