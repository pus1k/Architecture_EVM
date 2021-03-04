#ifndef MY_TERM_H
#define MY_TERM_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

using std::cout;
using std::endl;

enum colors {
    black = 30,
    red = 31,
    green = 32,
    yellow = 33,
    blue = 34,
    pink = 35,
    lightblue = 36,
    white = 37,
};

int mt_clrscr()
{
    cout << "\033[H\033[J";
    return 0;
}
int mt_gotoXY(int row, int col)
{
    cout << "\033[" << row << ";" << col << "H";
    return 0;
}
int mt_getscreensize(int* rows, int* cols)
{
    struct winsize w;
    if (!ioctl(1, TIOCGWINSZ, &w)) {
        *rows = w.ws_row;
        *cols = w.ws_col;
    } else
        return 1;
    return 0;
}
int mt_setfgcolor(colors clr)
{
    if ((int)clr < 30 || (int)clr > 37) {
        return 1;
    }
    cout << "\033[" << (int)clr << "m";
    return 0;
}
int mt_setbgcolor(colors clr)
{
    if ((int)clr < 30 || (int)clr > 37) {
        return 1;
    }
    cout << "\033[" << ((int)clr + 10) << "m";
    return 0;
}
int mt_setdefaultcolor()
{
    cout << "\033[0m";
    return 0;
}
#endif

/*
"\033[39m\\033[39m - Reset colour"
"\\033[2K - Clear Line"
"\\033[<L>;<C>H OR \\033[<L>;<C>f puts the cursor at line L and column C."
"\\033[<N>A Move the cursor up N lines"
"\\033[<N>B Move the cursor down N lines"
"\\033[<N>C Move the cursor forward N columns"
"\\033[<N>D Move the cursor backward N columns"
"\\033[2J Clear the screen, move to (0,0)"
"\\033[K Erase to end of line"
"\\033[s Save cursor position"
"\\033[u Restore cursor position"

"\\033[4m  Underline on"
"\\033[24m Underline off"
"\\033[1m  Bold on"
"\\033[21m Bold off"
*/