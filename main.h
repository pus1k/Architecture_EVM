#ifndef MAIN_H
#define MAIN_H

#include "lab2/simple_computer.h"

int temp = instructionCounter;

void clean_input()
{
    int rows, cols;
    mt_getscreensize(&rows, &cols);
    for (int i = 26; i <= 27; i++) {
        for (int j = 1; j < cols; j++) {
            mt_gotoXY(i, j);
            cout << " ";
        }
    }
}

void move(int i)
{
    int x = 3, y = 2;
    if (temp == 100)
        x = 12, y = 56;
    else {
        x += temp / 10;
        y += temp % 10 * 6;
    }
    mt_gotoXY(x, y);
    if (i) {
        mt_setbgcolor(white);
        mt_setfgcolor(black);
    } else {
        mt_setbgcolor(def);
        mt_setfgcolor(def);
    }
    printf("+%04x", memory[temp]);
    mt_setdefaultcolor();
}

void _UP_()
{
    if (temp > 9) {
        move(0);
        temp -= 10;
        move(1);
    }
}

void _DOWN_()
{
    if (temp < 91) {
        move(0);
        temp += 10;
        move(1);
    }
}

void _RIGHT_()
{
    if (temp != 99) {
        move(0);
        temp++;
        move(1);
    }
}

void _LEFT_()
{
    if (temp != 0) {
        move(0);
        temp--;
        move(1);
    }
}
void _SAVE_()
{
    string file_name;
    mt_gotoXY(26, 1);
    printf("File name for save RAM values: ");
    std::getline(cin, file_name);
    sc_memorySave(file_name);
    sleep(2);
    clean_input();
}
void _LOAD_()
{
    string file_name;
    mt_gotoXY(26, 1);
    printf("File name for load RAM values: ");
    std::getline(cin, file_name);
    sc_memoryLoad(file_name);
    sleep(2);
    clean_input();
}
void _F5_()
{
    sc_memoryGet(instructionCounter, &accumulator);
    mt_gotoXY(3, 71);
    printf("+%04x ", accumulator);
}
void _F6_()
{
    instructionCounter = temp;
    mt_gotoXY(6, 71);
    printf("+%04x ", instructionCounter);
    sc_memoryGet(65, &value);
    print_mem(value, def, def);
}
void _ENTER_()
{
    int value;
    mt_gotoXY(26, 1);
    printf("Input new value of memory: ");
    cin >> value;
    if (value <= 0x7fff) {
        if (!sc_memorySet(temp, value)) {
            cout << "Succesfull!";
        } else {
            cout << "Error!";
        }
    }
    // sleep(2);
    clean_input();
}

void _print_once_()
{
    bc_box(2, 1, 12, 62);
    mt_gotoXY(2, 30);
    cout << " Memory " << endl;
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
    bc_box(14, 1, 10, 46);
    mt_gotoXY(25, 1);
    cout << "Input/Output" << endl;
}
void _print_flag_()
{
    int value = 0;
    mt_gotoXY(12, 69);
    if (sc_regGet(OVERLOAD, &value) == 0) {
        if (value == 1) {
            cout << "P ";
            value = 0;
        }
    }
    if (sc_regGet(ZERO_DEL, &value) == 0) {
        if (value == 1) {
            cout << "O ";
            value = 0;
        }
    }
    if (sc_regGet(OUT_OF_BORDER, &value) == 0) {
        if (value == 1) {
            cout << "M ";
            value = 0;
        }
    }
    if (sc_regGet(IGNR_PULSES, &value) == 0) {
        if (value == 1) {
            cout << "T ";
            value = 0;
        }
    }
    if (sc_regGet(WRONG_COMMAND, &value) == 0) {
        if (value == 1) {
            cout << "E ";
            value = 0;
        }
    }
}
void _print_ram_()
{
    for (int i = 0, x = 3, y = 2, k = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            mt_gotoXY(x, y);
            if (sc_memoryGet(((i * 10) + j), &k) == 0)
                printf("+%04x ", k);
            y += 6;
        }
        x++, y = 2;
    }
}
void _print_screen_()
{
    move(1);
}
void _init_()
{
    std::system("clear");
    sc_init();
    _print_once_();
    _print_screen_();
    instructionCounter = 0;
    accumulator = 0;
    mt_gotoXY(6, 71);
    printf("+%04x ", instructionCounter);
}
#endif