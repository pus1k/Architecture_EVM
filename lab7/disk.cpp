#include "disk.h"
#include <iostream>

int main()
{
    tIDECHS geometry;
    cout << "Enter parametrs in IDECHS: " << endl;
    int goood = 1, temp = 0;
    while (good > 0) {
        if (good == 1) {
            cout << "C = ";
            cin >> temp;
            if (temp <= 1024) {
                geometry.C = temp, good = 2;
            }
            temp = 0;
        }
        if (good == 2) {
            cout << "H = ";
            cin >> temp;
            if (temp <= 16) {
                geometry.H = temp, good = 3;
            }
            temp = 0;
        }
        if (good == 3) {
            cout << "S = ";
            cin >> temp;
            if (temp <= 63) {
                geometry.S = temp, good = 0;
            }
            temp = 0;
        }
    }
    return 1;
}