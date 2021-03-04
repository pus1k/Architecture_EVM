#ifndef MY_BIG_CHARS_H
#define MY_BIG_CHARS_H

#include "../lab3/myTerm.h"
#include <cmath>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

#define ANGLE_LU "l"
#define ANGLE_LD "m"
#define ANGLE_RU "k"
#define ANGLE_RD "j"
#define LINE_VER "x"
#define LINE_HOR "q"
#define CUBE "a"

long int zero[2] = { 0b11111111110000111100001111000011, 0b11000011110000111100001111111111 };
long int one[2] = { 0b11111111000110000001100000011000, 0b00011000000111100001110000011000 };
long int two[2] = { 0b11111111000001100000110000011000, 0b00110000011000001100001101111110 };
long int three[2] = { 0b01111110110000110110000000110000, 0b00110000011000001100001101111110 };
long int four[2] = { 0b01100000011000001111111101100011, 0b01100110011011000111100001110000 };
long int five[2] = { 0b011111111110000001100000011000000, 0b11111111000000110000001111111111 };
long int six[2] = { 0b11111111110000111100001111000011, 0b11111111000000110000001111111111 };
long int seven[2] = { 0b00000011000001100000110000011000, 0b00110000011000001100000011111111 };
long int eight[2] = { 0b11111111110000111100001111000011, 0b11111111110000111100001111111111 };
long int nine[2] = { 0b11111111110000001100000011111111, 0b11000011110000111100001111111111 };
long int plus[2] = { 0b00011000000110000001100011111111, 0b11111111000110000001100000011000 };

int bc_printA(string str)
{
    cout << ("\033(0" + str + "\033(B");
    return 0;
}
int bc_box(int x1, int y1, int x2, int y2)
{
    if (x1 < 0 || y1 < 0)
        return -1;

    mt_gotoXY(x1, y1);
    bc_printA(ANGLE_LU);

    for (int i = y1 + 1; i < y1 + y2 - 1; i++) {
        mt_gotoXY(x1, i);
        bc_printA(LINE_HOR);
    }

    bc_printA(ANGLE_RU);

    for (int i = x1 + 1; i < x1 + x2 - 1; i++) {
        mt_gotoXY(i, y1);
        bc_printA(LINE_VER);
    }

    mt_gotoXY(x1 + x2 - 1, y1);
    bc_printA(ANGLE_LD);

    for (int i = x1 + 1; i < x1 + x2 - 1; i++) {
        mt_gotoXY(i, y1 + y2 - 1);
        bc_printA(LINE_VER);
    }

    for (int i = y1 + 1; i < y1 + y2 - 1; i++) {
        mt_gotoXY(x1 + x2 - 1, i);
        bc_printA(LINE_HOR);
    }

    bc_printA(ANGLE_RD);
    printf("\n");

    return 0;
}
int bc_printbigchar(long int* a, int x, int y)
{
    mt_gotoXY(x, y);
    for (int j = 1; j != -1; j--) {
        for (int byte = 0; byte < 4; byte++) {
            for (int bit = 0; bit < 8; bit++) {
                if (((a[j] >> (bit + (byte * 8))) & 0x1) == 0x1) {
                    bc_printA(CUBE);
                } else {
                    cout << " ";
                }
            }
            x++;
            mt_gotoXY(x, y);
        }
    }
    return 0;
}
void print_mem(int value)
{
    int temp = value;
    int del = 1000;
    int y = 2;
    bc_printbigchar(plus, 15, y);
    y += 9;
    int dig = 0;
    while (del >= 1) {
        dig = temp / del;
        temp %= del;
        del /= 10;
        switch (dig) {
        case (0):
            bc_printbigchar(zero, 15, y);
            break;
        case (1):
            bc_printbigchar(one, 15, y);
            break;
        case (2):
            bc_printbigchar(two, 15, y);
            break;
        case (3):
            bc_printbigchar(three, 15, y);
            break;
        case (4):
            bc_printbigchar(four, 15, y);
            break;
        case (5):
            bc_printbigchar(five, 15, y);
            break;
        case (6):
            bc_printbigchar(six, 15, y);
            break;
        case (7):
            bc_printbigchar(seven, 15, y);
            break;
        case (8):
            bc_printbigchar(eight, 15, y);
            break;
        case (9):
            bc_printbigchar(nine, 15, y);
        }
        y += 9;
    }
}
// int bc_setbigcharpos(int* big, int x, int y, int value);
// int bc_getbigcharpos(int* big, int x, int y, int* value);
// int bc_bigcharwrite(int fd, int* big, int count);
// int bc_bigcharread(int fd, int* big, int need_count, int* count);

#endif