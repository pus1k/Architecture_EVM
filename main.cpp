#include "main.h"

int main()
{
    int rows, cols;
    if (mt_getscreensize(&rows, &cols) == 0) {
        if (rows >= 26 && cols >= 84) {
            _init_();
            while (key != EXIT) {
                _print_screen_();
                rk_readkey(&key);
                switch (key) {
                case (key_right):
                    _RIGHT_();
                    break;
                case (key_down):
                    _DOWN_();
                    break;
                case (key_up):
                    _UP_();
                    break;
                case (key_left):
                    _LEFT_();
                    break;
                case (key_load):
                    _LOAD_();
                    break;
                case (key_save):
                    _SAVE_();
                    break;
                case (key_run):
                    break;
                case (key_step):
                    break;
                case (key_reset):
                    _init_();
                    break;
                case (key_f5):
                    _F5_();
                    break;
                case (key_f6):
                    _F6_();
                    break;
                default:
                    break;
                }
            }
        } else {
            mt_gotoXY(abs(rows / 2) + 1, abs(cols / 2) - 15);
            cout << "Make the terminal window bigger." << endl;
            mt_gotoXY(1, 1);
            return 0;
        }
    }
    return 0;
}
