all: main

main: main.o prefix_trie.o
	g++ -g -Wall -o main main.o prefix_trie.o

main.o:
	g++ -g -Wall -o main.o -c main.cpp
prefix_trie.o:
	g++ -g -Wall -o prefix_trie.o -c prefix_trie.cpp

clean:
	rm main main.o prefix_trie.o