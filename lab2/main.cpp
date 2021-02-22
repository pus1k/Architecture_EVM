#include "simple_computer.h"

int main()
{
    SimpleComputer SC;
    int value = 5;
    SC.sc_memoryGet(5, &value);
    std::cout << value << std::endl;

    for (int i = 0; i < N; i++) {
        SC.sc_memorySet(i, i);
    }

    SC.sc_memoryGet(5, &value);
    std::cout << value << std::endl;

    char* name = new char[100];
    name = "file.txt";
    SC.sc_memorySave(name);

    for (int i = 0; i < N; i++) {
        SC.sc_memorySet(i, 0);
    }

    SC.sc_memoryGet(5, &value);
    std::cout << value << std::endl;

    SC.sc_memoryLoad(name);

    SC.sc_memoryGet(5, &value);
    std::cout << value << std::endl;
}