#include "main.h"

int main()
{
    int rows, cols;
    if (mt_getscreensize(&rows, &cols) == 0) {
        if (rows >= 26 && cols >= 84) {
            _start_prog_();
        } else {
            mt_gotoXY(abs(rows / 2) + 1, abs(cols / 2) - 15);
            cout << "Make the terminal window bigger." << endl;
            mt_gotoXY(1, 1);
            return 0;
        }
    }
    return 0;
}