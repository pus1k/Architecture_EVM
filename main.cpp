#include "lab2/simple_computer.h"
#include "lab3/myTerm.h"

int main()
{
    SimpleComputer SC;
    int rows, cols;
    if (mt_getscreensize(&rows, &cols) == 0) {
        if (rows >= 16 && cols >= 10) {
            cout << "Memory" << endl;
            for (int i = 0, k = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    mt_gotoXY(i, j);
                    if (sc_memoryGet(((i + 1) * (j + 1)), &k) == 0)
                        cout << k;
                }
            }
        }
    }
    return 0;
}