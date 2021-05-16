#ifndef CPU_H
#define CPU_H

#include "../func.h"

int ALU(int command, int operand)
{
    int value = -1;
    sc_memoryGet(operand, &value);
    if (operand > 99 || value == -1) {
        return 1;
    }
    if (command == 0x30) {
        if ((accumulator + value) >= 0x9999) { // ADD
            sc_regSet(OVERLOAD, 1);
            return 1;
        }
        accumulator += value;
    } else if (command == 0x31) {
        if ((accumulator - value) < -0x9999) { // SUB
            sc_regSet(OVERLOAD, 1);
            return 1;
        }
        accumulator -= value;
    } else if (command == 0x32) {
        if (value == 0x0 || accumulator == 0x0) { // DIVIDE
            sc_regSet(ZERO_DEL, 1);
            return 1;
        }
        accumulator /= value;
    } else if (command == 0x33) {
        if ((accumulator * value) >= 0x9999) { // MUL
            sc_regSet(OVERLOAD, 1);
            return 1;
        }
        accumulator *= value;
    }
    return 0;
}

int CU()
{
    int command = 0, operand = 0, value = 0;
    if (sc_commandDecode(memory[instructionCounter], &command, &operand)) {
        sc_regSet(IGNR_PULSES, 1);
        sc_regSet(WRONG_COMMAND, 1);
        return 1;
    }
    if (command > 0x33 || command < 0x30) {
        if (command == 0x10) { // READ
            int value = 0;
            mt_gotoXY((operand / 10) + 3, operand % 10 * 6 + 2);
            cout << "      ";
            mt_gotoXY((operand / 10) + 3, operand % 10 * 6 + 3);
            cin.clear();
            rk_mytermregime(1, 0, 1, 0, 0);
            cin >> std::hex >> value;
            rk_mytermrestore();
            cin.clear();
            if (value < 0xffff) {
                sc_memorySet(operand, value);
            } else {
                sc_memorySet(operand, 0xffff);
                sc_regSet(OVERLOAD, 1);
            }
            cout << endl;
        } else if (command == 0x11) { // WRITE
            mt_gotoXY(26, 1);
            sc_memoryGet(operand, &value);
            printf("%x == %d\n", value, value);
            sleep(1);
        } else if (command == 0x20) { // LOAD
            sc_memoryGet(operand, &accumulator);
        } else if (command == 0x21) { // STORE
            if (accumulator < 0x9999) {
                sc_memorySet(operand, accumulator);
            } else {
                sc_memorySet(operand, 0x9999);
                sc_regSet(OVERLOAD, 1);
            }
        } else if (command == 0x40) { // JUMP
            if (operand > 99) {
                sc_regSet(OUT_OF_BORDER, 1);
            } else {
                instructionCounter = operand - 1;
            }
        } else if (command == 0x41) { // JNEG
            if (accumulator < 0) {
                instructionCounter = operand - 1;
            }
        } else if (command == 0x42) { // JZ
            if (accumulator == 0) {
                instructionCounter = operand - 1;
            }
        } else if (command == 0x43) { // HALT
            sc_regSet(IGNR_PULSES, 0);
            return 1;
        } else if (command == 0x63) { // RCR
            value = (operand << 5) & 0b1100000;
            accumulator = (operand >> 2) | value;
        }
    } else {
        if (ALU(command, operand)) {
            return 1;
        }
    }
    instructionCounter++;
    return 0;
}
#endif