#ifndef MY_BIG_CHARS_H
#define MY_BIG_CHARS_H

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
// int bc_printbigchar(int a[2], int x, int y, enum color, enum color);
// int bc_setbigcharpos(int* big, int x, int y, int value);
// int bc_getbigcharpos(int* big, int x, int y, int* value);
// int bc_bigcharwrite(int fd, int* big, int count);
// int bc_bigcharread(int fd, int* big, int need_count, int* count);

#endif