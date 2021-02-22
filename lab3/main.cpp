#include "myTerm.h"

int main()
{
    mt_gotoXY(5, 5);
    char ans;
    std::cin >> ans;
    mt_clrscr();
    mt_setfgcolor(red);
    std::cin >> ans;
    int rows, cols;
    mt_setbgcolor(white);
    mt_getscreensize(&rows, &cols);
    cout << rows << " " << cols << endl;
    mt_setdefaultcolor();
}