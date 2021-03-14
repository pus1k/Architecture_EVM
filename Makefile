all: tet clear

tet:	
	g++ -Wall -Werror -o tet main.cpp
clear:
	clear
clean: 
	rm -rf tet *.txt 
	clear