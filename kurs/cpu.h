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
        if ((accumulator + value) >= 0x9999) {
            sc_regSet(OVERLOAD, 1);
            return 1;
        }
        accumulator += value;
    } else if (command == 0x31) {
        if ((accumulator - value) < -0x9999) {
            sc_regSet(OVERLOAD, 1);
            return 1;
        }
        accumulator -= value;
    } else if (command == 0x32) {
        if (value == 0x0 || accumulator == 0x0) {
            sc_regSet(ZERO_DEL, 1);
            return 1;
        }
        accumulator /= value;
    } else if (command == 0x33) {
        if ((accumulator * value) >= 0x9999) {
            sc_regSet(OVERLOAD, 1);
            return 1;
        }
        accumulator *= value;
    }
    return 0;
}

// // Using for break the loop
// struct guard {
//     int value;
//     struct guard* next;
// };

// int temp[5];
// int temp_n[5];
// int temp_counter = 0;

// int check_temp()
// {
//     struct guard* list = new struct guard;
//     list->value = temp[0];
//     list->next = NULL;
//     struct guard* pop = list;
//     int count = 1;
//     for (int i = 1; i < temp_counter; i++) {
//         pop = list;
//         do {
//             if (temp[i] == pop->value) {
//                 break;
//             }
//             pop = pop->next;
//         } while (pop->next);
//         if (pop) {
//             count++;
//         } else {
//             struct guard* child = new struct guard;
//             child->next = NULL;
//             child->value = temp[i];
//             pop->next = child;
//         }
//     }
//     if (temp_counter - count < 3) {
//         return 1;
//     }
//     return 0;
// }

int CU()
{
    int command = 0;
    int operand = 0;
    int value = 0;
    if (sc_commandDecode(memory[instructionCounter], &command, &operand)) {
        sc_regSet(IGNR_PULSES, 1);
        sc_regSet(WRONG_COMMAND, 1);
        return 1;
    }
    // temp[temp_counter] = memory[instructionCounter];
    // temp_counter++;
    // if (temp_counter == 5) {
    //     if (check_temp()) {
    //         sc_regSet(IGNR_PULSES, 1);
    //         return 2;
    //     }
    // }
    if (command > 0x33 || command < 0x30) {
        if (command == 0x10) { // READ
            ENTER();
        } else if (command == 0x11) { // WRITE
            mt_gotoXY(26, 1);
            sc_memoryGet(operand, &value);
            printf("%x\n", value);
            sleep(2);
            clean_input();
        } else if (command == 0x20) { // LOAD
            sc_memoryGet(operand, &accumulator);
        } else if (command == 0x21) { // STORE
            if (!sc_commandEncode((accumulator >> 7) & 0x7F, accumulator & 0x7F, &value))
                sc_memorySet(operand, value);
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
            return 2;
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