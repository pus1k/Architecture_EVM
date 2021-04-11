#ifndef MAIN_H
#define MAIN_H

#include "kurs/cpu.h"

// sc_regSet(IGNR_TIMER, 1);

void _init_()
{
    srand(time(0));
    std::system("clear");
    sc_init();
    instructionCounter = 0;
    accumulator = 0;
    for (int i = 0; i < N; i++) {
        int value = 0;
        value = (commands[(rand() % 12 + 0)] << 7) | (rand() % 99 + 0);
        sc_memorySet(i, value);
    }
    _print_box_();
    _print_once_();
}

void _timer_(int signo)
{
    int value = 0;
    sc_regGet(IGNR_TIMER, &value);
    if (instructionCounter < 99 && !value) {
        instructionCounter++;
    }
    sc_regGet(IGNR_PULSES, &value);
    if (!value) {
        while (value == 0) {
            _print_screen_();
            value = CU();
            sleep(1);
        }
        if (value == 2) {
            sc_regSet(IGNR_PULSES, 1);
            alarm(0);
        }
    } else {
        alarm(0);
    }
    _print_screen_();
}

void _signal_(int signo)
{
    _init_();
}

void _start_prog_()
{
    signal(SIGALRM, _timer_);
    signal(SIGUSR1, _signal_);
    nval.it_interval.tv_sec = 1;
    nval.it_interval.tv_usec = 0;
    nval.it_value.tv_sec = 1;
    nval.it_value.tv_usec = 0;
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
            if (instructionCounter < 99)
                instructionCounter++;
        } else if (key == key_down) {
            if (instructionCounter < 90)
                instructionCounter += 10;
        } else if (key == key_up) {
            if (instructionCounter > 9)
                instructionCounter -= 10;
        } else if (key == key_left) {
            if (instructionCounter > 0)
                instructionCounter--;
        } else if (key == key_load) {
            LOAD();
        } else if (key == key_save) {
            SAVE();
        } else if (key == key_enter) {
            ENTER();
        } else if (key == key_run) {
            setitimer(ITIMER_REAL, &nval, &oval);
        } else if (key == key_step) {
            _print_screen_();
            sc_regGet(IGNR_PULSES, &value);
            if (!value)
                CU();
        } else if (key == key_reset) {
            alarm(0);
            raise(SIGUSR1);
        } else if (key == key_f5) {
            F5();
        } else if (key == key_f6) {
            F6();
        }
    }
}
#endif