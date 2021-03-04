#include "lab2/simple_computer.h"
#include "lab3/myTerm.h"
#include "lab4/myBigChars.h"
#include <iomanip>

int main()
{
    SimpleComputer SC;
    int rows, cols;
    SC.sc_regSet(OVERLOAD, 1);
    SC.sc_regSet(ZERO_DEL, 1);
    SC.sc_regSet(OUT_OF_BORDER, 1);
    SC.sc_regSet(IGNR_PULSES, 1);
    SC.sc_regSet(WRONG_COMMAND, 1);
    for (int i = 0; i < 100; i++) {
        SC.sc_memorySet(i, (i + 9900));
    }
    if (mt_getscreensize(&rows, &cols) == 0) {
        if (rows >= 25 && cols >= 84) {
            bc_box(2, 1, 12, 62);
            mt_gotoXY(2, 30);
            cout << " Memory " << endl;
            for (int i = 0, x = 3, y = 2, k = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    mt_gotoXY(x, y);
                    if (SC.sc_memoryGet(((i * 10) + j), &k) == 0)
                        cout << "+" << std::setw(4) << std::setfill('0') << k << " ";
                    y += 6;
                }
                x++, y = 2;
            }
            bc_box(2, 63, 3, 22);
            mt_gotoXY(2, 67);
            cout << " accumulator ";
            bc_box(5, 63, 3, 22);
            mt_gotoXY(5, 64);
            cout << " instructionCounter ";
            bc_box(8, 63, 3, 22);
            mt_gotoXY(8, 68);
            cout << " Operation ";
            bc_box(11, 63, 3, 22);
            mt_gotoXY(11, 70);
            cout << " Flags ";
            int value = -1;
            mt_gotoXY(12, 69);
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

            bc_box(14, 1, 10, 46);
            SC.sc_memoryGet(65, &value);
            print_mem(value);
            bc_box(14, 47, 10, 38);
            mt_gotoXY(14, 48);
            cout << " Keys: ";
            mt_gotoXY(15, 48);
            cout << "l - load";
            mt_gotoXY(16, 48);
            cout << "s - save";
            mt_gotoXY(17, 48);
            cout << "r - run";
            mt_gotoXY(18, 48);
            cout << "t - step";
            mt_gotoXY(19, 48);
            cout << "i - reset";
            mt_gotoXY(20, 48);
            cout << "F5 - accumulator";
            mt_gotoXY(21, 48);
            cout << "F6 - instructionCounter";
            mt_gotoXY(26, 1);
        }

        return 0;
    }
}