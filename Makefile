all: tet sat bsc clear

O: clean tet sat bsc clear

tet: build/main.o	
	g++ -o tet build/main.o 
sat: build/asm.o
	g++ -o sat build/asm.o
bsc: build/basic.o
	g++ -o bsc build/basic.o
build/basic.o: kurs/basic.cpp
	g++ -Wall -Werror -o build/basic.o -c kurs/basic.cpp
build/asm.o: kurs/asm.cpp
	g++ -Wall -Werror -o build/asm.o -c kurs/asm.cpp
build/main.o: main.cpp
	g++ -Wall -Werror -o build/main.o -c main.cpp 
clear:
	clear
clean: 
	rm -rf tet sat *.o *.txt build/*.o
	clear
.PHONY: clean clear O 