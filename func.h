#ifndef FUNC_H
#define FUNC_H

#include "lab2/simple_computer.h"
#include <signal.h>
#include <stdio.h>
#include <sys/time.h>

struct itimerval nval, oval;

void print_mem(int value, colors fc, colors bc)
{
    int temp = value;
    int dig[4];
    bc_printbigchar(plus, 15, 2, fc, bc);
    for (int i = 0; i < 4; i++) {
        dig[i] = 0, dig[i] = temp % 16, temp /= 16;
    }
    bc_printbigchar(CHARS[dig[3]], 15, 11, fc, bc);
    bc_printbigchar(CHARS[dig[2]], 15, 20, fc, bc);
    bc_printbigchar(CHARS[dig[1]], 15, 29, fc, bc);
    bc_printbigchar(CHARS[dig[0]], 15, 38, fc, bc);
}

void clean_input()
{
    int rows, cols;
    mt_getscreensize(&rows, &cols);
    for (int i = 26; i <= 30; i++) {
        for (int j = 1; j < cols; j++) {
            mt_gotoXY(i, j);
            cout << " ";
        }
    }
}

void SAVE()
{
    string file_name;
    mt_gotoXY(26, 1);
    printf("File name for save RAM values: ");
    std::getline(cin, file_name);
    sc_memorySave(file_name);
    sleep(2);
    clean_input();
}

void LOAD()
{
    string file_name;
    mt_gotoXY(26, 1);
    printf("File name for load RAM values: ");
    std::getline(cin, file_name);
    sc_memoryLoad(file_name);
    sleep(2);
    clean_input();
}

void F5()
{
    char ans = 'n';
    cout << "Do you wanna use value from instructionCounter cell (y / n): ";
    rk_mytermregime(1, 0, 1, 0, 0);
    cin >> ans;
    rk_mytermrestore();
    if (ans == 'y') {
        sc_memoryGet(instructionCounter, &accumulator);
    } else {
        cout << "\nEnter value for accumulator (0 <--> 7fff): ";
        cin >> std::hex >> accumulator;
    }
    mt_gotoXY(3, 71);
    printf("+%04x ", accumulator);
    clean_input();
}
void F6()
{
    cout << "Enter value for instructionCounter (0 <--> 99): ";
    cin >> instructionCounter;
    if (instructionCounter < 0) {
        instructionCounter = 0;
    } else if (instructionCounter > 99) {
        instructionCounter = 99;
    }
    clean_input();
}

// DO CPU
void RUN()
{
    return;
}
void STEP()
{
    return;
}

void ENTER()
{
    int value = 0, temp = 0;
    mt_gotoXY(26, 1);
    cout << "> ";
    cin >> std::hex >> value;
    if (!sc_commandEncode((value >> 7) & 0x7F, value & 0x7F, &temp)) {
        if (sc_memorySet(instructionCounter, temp)) {
            cout << "Out of memory border!" << endl;
            sleep(1);
        }
    } else {
        cout << "Value is not correct!" << endl;
        sleep(1);
    }
    cout << endl;
    clean_input();
}

void _print_box_()
{
    bc_box(2, 1, 12, 62);
    bc_box(2, 63, 3, 22);
    bc_box(5, 63, 3, 22);
    bc_box(8, 63, 3, 22);
    bc_box(11, 63, 3, 22);
    bc_box(14, 47, 10, 38);
    bc_box(14, 1, 10, 46);
}
void _print_once_()
{
    mt_gotoXY(2, 30);
    cout << " Memory ";
    mt_gotoXY(2, 67);
    cout << " accumulator ";
    mt_gotoXY(3, 71);
    printf("+%04x ", accumulator);
    mt_gotoXY(5, 64);
    cout << " instructionCounter ";
    mt_gotoXY(8, 68);
    cout << " Operation ";
    mt_gotoXY(11, 70);
    cout << " Flags ";
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
    cout << "Enter - change value";
    mt_gotoXY(21, 48);
    cout << "F5 - accumulator";
    mt_gotoXY(22, 48);
    cout << "F6 - instructionCounter";
}
void _print_screen_()
{
    for (int i = 0, x = 3, y = 2, k = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            mt_gotoXY(x, y);
            if (sc_memoryGet(((i * 10) + j), &k) == 0) {
                if ((i * 10 + j) == instructionCounter) {
                    mt_setbgcolor(white);
                    mt_setfgcolor(black);
                }
                if (((k >> 14) & 1) == 0)
                    printf("+%04x ", k);
                else
                    printf("-%04x ", k);
                mt_setdefaultcolor();
            }
            y += 6;
        }
        x++, y = 2;
    }
    int value = 0;
    mt_gotoXY(6, 71);
    printf("+%04x ", instructionCounter);
    mt_gotoXY(9, 64);
    cout << "                    ";
    mt_gotoXY(9, 69);
    int command = 0, operand = 0;
    sc_commandDecode(memory[instructionCounter], &command, &operand);
    printf("+%02x : %02x", command, operand);
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
    sc_memoryGet(instructionCounter, &value);
    print_mem(value, def, def);
    mt_gotoXY(25, 1);
    cout << "Input/Output" << endl;
}

#endif