all: tet clear

O: clean tet clear

tet: build/main.o	
	g++ -o tet build/main.o
build/main.o: main.cpp
	g++ -Wall -Werror -o build/main.o -c main.cpp
clear:
	clear
clean: 
	rm -rf tet *.txt build/*.o
	clear