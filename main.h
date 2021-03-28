#ifndef MAIN_H
#define MAIN_H

#include "func.h"

void _timer_(int signo)
{
    int value = 0;
    sc_regGet(IGNR_TIMER, &value);
    if (instructionCounter < 99 && !value) {
        instructionCounter++;
        mt_gotoXY(6, 71);
        printf("+%04x ", instructionCounter);
        mt_gotoXY(26, 1);
    } else {
        sc_regSet(IGNR_TIMER, 1);
        alarm(0);
    }
}
void _signal_(int signo);
void _init_()
{
    srand(time(0));
    std::system("clear");
    sc_init();
    instructionCounter = temp = 0;
    accumulator = 0;
    for (int i = 0; i < N; i++)
        sc_memorySet(i, rand() % 0x3B7f + 0);
    _print_box_();
    _print_once_();
    signal(SIGALRM, _timer_);
    signal(SIGUSR1, _signal_);
    nval.it_interval.tv_sec = 1;
    nval.it_interval.tv_usec = 0;
    nval.it_value.tv_sec = 1;
    nval.it_value.tv_usec = 0;
}

void _signal_(int signo)
{
    _init_();
}

void _start_prog_()
{
    int value = 0;
    _init_();
    setitimer(ITIMER_REAL, &nval, &oval);
    while (key != EXIT) {
        _print_screen_();
        sc_regGet(IGNR_TIMER, &value);
        if (!value) {
            rk_readkey(&key);
        } else {
            key = key_reset;
        }
        if (key == key_right) {
            if (temp < 99)
                temp++;
        } else if (key == key_down) {
            if (temp < 90)
                temp += 10;
        } else if (key == key_up) {
            if (temp > 9)
                temp -= 10;
        } else if (key == key_left) {
            if (temp > 0)
                temp--;
        } else if (key == key_load) {
            LOAD();
        } else if (key == key_save) {
            SAVE();
        } else if (key == key_enter) {
            ENTER();
        } else if (key == key_run) {
            RUN();
        } else if (key == key_step) {
            STEP();
        } else if (key == key_reset) {
            raise(SIGUSR1);
        } else if (key == key_f5) {
            F5();
        } else if (key == key_f6) {
            F6();
        } else if (key == key_signal) {
            setitimer(ITIMER_REAL, &nval, &oval);
        }
    }
}
#endif