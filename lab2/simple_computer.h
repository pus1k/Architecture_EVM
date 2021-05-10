#ifndef SIMPLE_COMPUTER
#define SIMPLE_COMPUTER

#include "../lab4/myBigChars.h"
#include "../lab5/myReadKey.h"
#include <fstream>
#include <iostream>
#include <string>

using std::cout;

#define N 100
#define OVERLOAD 0 // P
#define ZERO_DEL 1 //  O
#define OUT_OF_BORDER 2 // M
#define IGNR_PULSES 3 // T
#define WRONG_COMMAND 4 // E

int memory[N];
int flag = 0;
const int ncommands = 13;
const int commands[ncommands] = { 0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 0x40, 0x41, 0x42, 0x43, 0x63 };

int is_command(int value)
{
    for (int i = 0; i < ncommands; i++) {
        if (commands[i] == value) {
            return 0;
        }
    }
    return 1;
}

int sc_init()
{
    for (int i = 0; i < N; i++)
        memory[i] = 0;
    flag = 0;
    return 0;
}
int sc_regSet(int reg, int value)
{
    if (reg == OVERLOAD || reg == ZERO_DEL
        || reg == OUT_OF_BORDER || reg == IGNR_PULSES
        || reg == WRONG_COMMAND) {
        if (value == 1) {
            flag |= (1 << reg);
            return 0;
        } else if (value == 0) {
            flag &= ~(1 << reg);
            return 0;
        }
    }
    return 1;
}
int sc_regGet(int reg, int* value)
{
    if (reg == OVERLOAD || reg == ZERO_DEL
        || reg == OUT_OF_BORDER || reg == IGNR_PULSES
        || reg == WRONG_COMMAND) {
        *value = (flag >> reg) & 1;
        return 0;
    }
    return 1;
}
int sc_memorySet(int address, int value)
{
    if (address < N || address >= 0) {
        memory[address] = value;
        return 0;
    }
    sc_regSet(OUT_OF_BORDER, 1);
    return 1;
}
int sc_memoryGet(int address, int* value)
{
    if (address < N || address >= 0) {
        *value = memory[address];
        return 0;
    }
    sc_regSet(OUT_OF_BORDER, 1);
    return 1;
}
int sc_memorySave(string filename)
{
    std::ofstream out(filename, std::ios::binary);
    if (out.is_open()) {
        for (int i = 0; i < N; i++) {
            out.write((char*)&memory[i], sizeof(memory[i]));
        }
        std::cout << "Save succesfully!" << std::endl;
        return 0;
    }
    std::cout << "Error:File is not opened!" << std::endl;
    return 1;
}
int sc_memoryLoad(string filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in.is_open()) {
        for (int i = 0; i < N; i++) {
            in.read((char*)&memory[i], sizeof(memory[i]));
        }
        std::cout << "Load succesfully!" << std::endl;
        return 0;
    }
    std::cout << "Error:File is not opened!" << std::endl;
    return 1;
}
int sc_regInit()
{
    flag = 0;
    return 0;
}

int sc_commandEncode(int command, int operand, int* value)
{
    sc_regSet(WRONG_COMMAND, 0);
    if (!is_command(command)) {
        if (operand > -1 && operand < 128) {
            *value = (command << 7) | operand;
            return 0;
        } else {
            return 1;
        }
    } else {
        sc_regSet(WRONG_COMMAND, 1);
        return 1;
    }
}
int sc_commandDecode(int value, int* command, int* operand)
{
    int command_sign;
    int temp_command, temp_operand;
    sc_regSet(WRONG_COMMAND, 0);
    command_sign = (value >> 14) & 1;
    if (command_sign == 0) {
        temp_command = (value >> 7) & 0x7F;
        temp_operand = value & 0x7F;
        if (!is_command(temp_command)) {
            if (temp_operand >= 0 && temp_operand < 128) {
                *command = temp_command;
                *operand = temp_operand;
                return 0;
            }
        }
    }
    sc_regSet(WRONG_COMMAND, 1);
    return 1;
}
#endif