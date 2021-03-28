#ifndef CPU_H
#define CPU_H

#include "../lab2/simple_computer.h"

#define READ 10
#define WRITE 11

#define LOAD 20
#define STORE 21

#define ADD 30
#define SUB 31
#define DIVIDE 32
#define MUL 33

#define JUMP 40
#define JNEG 41
#define JZ 42
#define HALT 43
#define JB 44
#define JC 56
#define SET 78

int mem_temp[100];

int ALU(int command, int operand)
{
    if (operand > 99) {
        return 1;
    }

    switch (command) {
    case ADD:
        if ((accum + ptr_str[operand]) >= 65535) {
            sc_regSet(OD, 1);
            break;
        }
        accum += ptr_str[operand];
        break;
    case SUB:
        if ((accum - ptr_str[operand]) < -65534) {
            sc_regSet(OD, 1);
            break;
        }
        accum -= ptr_str[operand];
        break;
    case DIVIDE:
        if (ptr_str[operand] == 0 || accum == 0) {
            sc_regSet(DE, 1);
            break;
        }
        accum /= ptr_str[operand];
        break;
    case MUL:
        if ((accum * ptr_str[operand]) >= 65535) {
            sc_regSet(OD, 1);
            break;
        }
        accum *= ptr_str[operand];
        break;
    default:
        return 1;
    }

    return 0;
}

int CPU()
{
    for (int i = 0; i < N; i++)
        mem_temp[i] = memory[i];

    int command = 0;
    int operand = 0;

    if (sc_commandDecode(mem_temp[instructionCounter], &command, &operand)) {
        sc_regSet(IGNR_PULSES, 1);
        return 1;
    }

    int value = 0;

    if (command > 33 || command < 30) {
        if (command == 10) {
            mt_gotoXY(26, 1);
            cout >> "> ";
            int tmp = 0;
            scanf("%d", &tmp);
            printf("\n");
            if (tmp > 65535) {
                sc_regSet(OD, 1);
                break;
            }
            ptr_str[operand] = tmp;
            incrementNumStrForLogs();
            break;
        case WRITE:
            mt_gotoXY(26 + numStrForLogs, 1);
            printf("%d\n", ptr_str[operand]);
            incrementNumStrForLogs();
            break;
        case LOAD:
            accum = ptr_str[operand];
            break;
        case STORE:
            ptr_str[operand] = accum;
            break;

        case JUMP:
            if (operand > 99 || operand < 0) {
                sc_regSet(EG, 1);
                break;
            }
            instCount = operand;
            instCount--;
            break;
        case JNEG:
            if (accum < 0) {
                instCount = operand;
                instCount--;
            }
            break;
        case JZ:
            if (accum == 0) {
                instCount = operand;
                instCount--;
            }
            break;
        case JC:
            sc_regGet(OD, &value);
            if (value == 1) {
                instCount = operand;
                instCount--;
            }
            break;
        case JB:
            if (accum > 0) {
                instCount = operand;
                instCount--;
            }
            break;

        case SET:
            accum = operand;
            break;

        case HALT:
            return 2;
            break;
        }
    } else {
        if (ALU(command, operand)) {
            return 1;
        }
    }

    instCount++;

    return 0;
}

#endif