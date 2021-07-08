all: simpleOrderBook

simpleOrderBook: Parser.o main.o
	g++ Parser.o main.o -o simpleOrderBook
	rm -rf *.o

main.o: main.cpp
	g++ -std=c++17 -Wall -pedantic -c main.cpp

Parser.o: parser/Parser.cpp parser/Parser.h
	g++ -std=c++17 -Wall -pedantic -c parser/Parser.cpp

clean:
	rm -rf *.o gzzip