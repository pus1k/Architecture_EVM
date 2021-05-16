all: tet sat clear

O: clean tet sat clear

tet: build/main.o	
	g++ -o tet build/main.o 
sat: build/asm.o
	g++ -o sat build/asm.o
build/asm.o: kurs/asm.cpp
	g++ -Wall -Werror -o build/asm.o -c kurs/asm.cpp
build/main.o: main.cpp
	g++ -Wall -Werror -o build/main.o -c main.cpp 
clear:
	clear
clean: 
	rm -rf tet sat *.o *.txt build/*.o
	clear
