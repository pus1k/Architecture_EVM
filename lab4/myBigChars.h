#ifndef MY_BIG_CHARS_H
#define MY_BIG_CHARS_H

#include "../lab3/myTerm.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
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
long int A[2] = { 0b01000010010000100100001001111110, 0b01000010010000100010010000011000 };
long int B[2] = { 0b00111110010000100100001001000010, 0b00111110010000100100001000111110 };
long int C[2] = { 0b01111110000000100000001000000010, 0b00000010000000100000001001111110 };
long int D[2] = { 0b00111110010000100100001001000010, 0b01000010010000100100001000111110 };
long int E[2] = { 0b01111110000000100000001000000010, 0b01111110000000100000001001111110 };
long int F[2] = { 0b00000010000000100000001000000010, 0b00111110000000100000001001111110 };

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
int bc_printbigchar(long int* a, int x, int y, colors fc, colors bc)
{
    mt_gotoXY(x, y);
    mt_setfgcolor(fc);
    mt_setbgcolor(bc);
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
    mt_setdefaultcolor();
    return 0;
}
void print_mem(int value, colors fc, colors bc)
{
    int temp = value;
    int del = 16;
    int y = 9;
    int dig[6] = { -1 };
    bc_printbigchar(plus, 15, 2, fc, bc);
    int i = 0;
    while (temp > del) {
        dig[i] = temp % del;
        temp /= del;
        i++;
    }
    dig[i] = temp;
    while (i >= 0) {
        switch (dig[i]) {
        case (0):
            bc_printbigchar(zero, 15, y, fc, bc);
            break;
        case (1):
            bc_printbigchar(one, 15, y, fc, bc);
            break;
        case (2):
            bc_printbigchar(two, 15, y, fc, bc);
            break;
        case (3):
            bc_printbigchar(three, 15, y, fc, bc);
            break;
        case (4):
            bc_printbigchar(four, 15, y, fc, bc);
            break;
        case (5):
            bc_printbigchar(five, 15, y, fc, bc);
            break;
        case (6):
            bc_printbigchar(six, 15, y, fc, bc);
            break;
        case (7):
            bc_printbigchar(seven, 15, y, fc, bc);
            break;
        case (8):
            bc_printbigchar(eight, 15, y, fc, bc);
            break;
        case (9):
            bc_printbigchar(nine, 15, y, fc, bc);
            break;
        case (10):
            bc_printbigchar(A, 15, y, fc, bc);
            break;
        case (11):
            bc_printbigchar(B, 15, y, fc, bc);
            break;
        case (12):
            bc_printbigchar(C, 15, y, fc, bc);
            break;
        case (13):
            bc_printbigchar(D, 15, y, fc, bc);
            break;
        case (14):
            bc_printbigchar(E, 15, y, fc, bc);
            break;
        case (15):
            bc_printbigchar(F, 15, y, fc, bc);
        }
        y += 9;
        i--;
    }
}
int bc_setbigcharpos(long int* big, int x, int y, int value)
{
    if (x < 0 || x > 7 || y < 0 || y > 7) {
        return 1;
    } else {
        int id = 1;
        if (y > 3) {
            id = 0;
            y -= 4;
        }
        if (value == 1 || value == 0) {
            if (value == 1) {
                big[id] |= 1 << (x + y * 8);
            } else {
                big[id] &= ~(1 << (x + y * 8));
            }
            return 0;
        }
    }
    return 1;
}
int bc_getbigcharpos(long int* big, int x, int y, int* value)
{
    if (x < 0 || x > 7 || y < 0 || y > 7) {
        return 1;
    } else {
        int id = 1;
        if (y > 3) {
            id = 0;
            y -= 4;
        }
        *value = (big[id] >> (x + y * 8)) & 1;
        return 0;
    }
    return 1;
}
int bc_bigcharwrite(std::string str, long int* big, int count)
{
    ofstream outfile(str, std::ios::binary);
    if (outfile.is_open()) {
        int i = 0;
        while (count > 0) {
            outfile.write((char*)&big[i], sizeof(big[i])), i++;
            outfile.write((char*)&big[i], sizeof(big[i])), i++;
            count--;
        }
        outfile.close();
        return 0;
    }
    return 1;
}
int bc_bigcharread(std::string str, long int* big, int need_count, int* count)
{
    ifstream infile(str, std::ios::binary);
    if (infile.is_open()) {
        int i = 0;
        while (need_count > 0) {
            infile.read((char*)&big[i], sizeof(big[i])), i++;
            infile.read((char*)&big[i], sizeof(big[i])), i++;
            need_count--;
            *count += 1;
        }
        infile.close();
        return 0;
    }
    return 1;
}

#endif