#ifndef MYREADKEY_H
#define MYREADKEY_H

#include <iostream>
#include <string.h>
#include <termios.h>
#include <unistd.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

enum keys {
    key_load,
    key_save,
    key_run,
    key_step,
    key_reset,
    key_f5,
    key_f6,
    key_up,
    key_down,
    key_left,
    key_right,
    key_other,
    key_enter,
    EXIT
};

static struct termios stored_settings;
keys key = key_other;

int rk_mytermsave()
{
    if (!tcgetattr(0, &stored_settings)) {
        return 1;
    }
    return 0;
}
int rk_mytermrestore()
{ // TCSANOW - changes works right now
    if (!tcsetattr(0, TCSANOW, &stored_settings)) {
        return 1;
    }
    return 0;
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
    struct termios new_settings = stored_settings;
    rk_mytermsave();
    if (regime == 1) {
        new_settings.c_lflag &= (~ICANON);
        if (sigint == 1) {
            new_settings.c_lflag &= (~ISIG);
        } else {
            new_settings.c_lflag |= ISIG;
        }
        if (echo == 1) {
            new_settings.c_lflag &= (~ECHO);
        } else {
            new_settings.c_lflag |= ECHO;
        }
        new_settings.c_cc[VMIN] = vmin;
        new_settings.c_cc[VTIME] = vtime;
    } else {
        new_settings.c_lflag |= ICANON;
    }
    tcsetattr(0, TCSANOW, &new_settings);
    return 0;
}

// tcflag_t c_iflag;      /* режимы ввода */
// tcflag_t c_oflag;      /* режимы вывода */
// tcflag_t c_cflag;      /* режимы управления */
// tcflag_t c_lflag;      /* режимы локали */
// cc_t c_cc[NCCS];       /* управляющие символы */

int rk_readkey(enum keys* key)
{
    rk_mytermregime(1, 0, 1, 1, 1);
    char buf[8];
    read(STDIN_FILENO, buf, 8);
    if (!strcmp(buf, "\033[A")) {
        *key = key_up;
    } else if (!strcmp(buf, "\033[B")) {
        *key = key_down;
    } else if (!strcmp(buf, "\033[C")) {
        *key = key_right;
    } else if (!strcmp(buf, "\033[D")) {
        *key = key_left;
    } else if (!strcmp(buf, "\033[15~")) {
        *key = key_f5;
    } else if (!strcmp(buf, "\033[17~")) {
        *key = key_f6;
    } else if (buf[0] == '\n') {
        *key = key_enter;
    } else if (buf[0] == 'l') {
        *key = key_load;
    } else if (buf[0] == 's') {
        *key = key_save;
    } else if (buf[0] == 'r') {
        *key = key_run;
    } else if (buf[0] == 't') {
        *key = key_step;
    } else if (buf[0] == 'i') {
        *key = key_reset;
    } else if ((int)buf[0] == 27) {
        *key = EXIT;
    } else {
        *key = key_other;
    }
    rk_mytermrestore();
    return 0;
}
#endif