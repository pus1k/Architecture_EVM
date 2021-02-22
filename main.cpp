#include "lab2/simple_computer.h"
#include "lab3/myTerm.h"

int main()
{
    SimpleComputer SC;
    int rows, cols;
    SC.sc_regSet(OVERLOAD, 1);
    SC.sc_regSet(ZERO_DEL, 1);
    SC.sc_regSet(OUT_OF_BORDER, 1);
    SC.sc_regSet(IGNR_PULSES, 1);
    SC.sc_regSet(WRONG_COMMAND, 1);
    if (mt_getscreensize(&rows, &cols) == 0) {
        if (rows >= 16 && cols >= 10) {
            cout << "Memory" << endl;
            for (int i = 0, k = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    mt_gotoXY(i + 3, j + 1);
                    if (SC.sc_memoryGet((i * j), &k) == 0)
                        cout << k << " ";
                }
            }
            mt_gotoXY(2, 13);
            cout << "Flags";
            int value = -1;
            mt_gotoXY(3, 13);
            if (SC.sc_regGet(OVERLOAD, &value) == 0) {
                if (value == 1) {
                    cout << "P ";
                }
            }
            value = -1;
            if (SC.sc_regGet(ZERO_DEL, &value) == 0) {
                if (value == 1) {
                    cout << "O ";
                }
            }
            value = -1;
            if (SC.sc_regGet(OUT_OF_BORDER, &value) == 0) {
                if (value == 1) {
                    cout << "M ";
                }
            }
            value = -1;
            if (SC.sc_regGet(IGNR_PULSES, &value) == 0) {
                if (value == 1) {
                    cout << "T ";
                }
            }
            value = -1;
            if (SC.sc_regGet(WRONG_COMMAND, &value) == 0) {
                if (value == 1) {
                    cout << "E ";
                }
            }
            value = -1;
            mt_gotoXY(2, 24);
            cout << "Keys";
            mt_gotoXY(3, 24);
            cout << "s - save";
            mt_gotoXY(4, 24);
            cout << "l - load";
            mt_gotoXY(13, 1);
        }
    }
    return 0;
}