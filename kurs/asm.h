#include "../lab2/simple_computer.h"
#include <iomanip>
#include <stdio.h>
#include <string.h>

int get_command(string str)
{
    int command = -1;
    if (str == "READ")
        command = 0x10;
    else if (str == "WRITE")
        command = 0x11;
    else if (str == "LOAD")
        command = 0x20;
    else if (str == "STORE")
        command = 0x21;
    else if (str == "ADD")
        command = 0x30;
    else if (str == "SUB")
        command = 0x31;
    else if (str == "DIVIDE")
        command = 0x32;
    else if (str == "MUL")
        command = 0x33;
    else if (str == "JUMP")
        command = 0x40;
    else if (str == "JNEG")
        command = 0x41;
    else if (str == "JZ")
        command = 0x42;
    else if (str == "HALT")
        command = 0x43;
    else if (str == "RCR")
        command = 0x63;
    else if (str == "=")
        command = 0;
    return command;
}

int find_pref(char* ar, int arg)
{
    int i = 0;
    while (ar[i] != 0) {
        i++;
        if (ar[i] == '.' && ar[i + 1] == 's' && ar[i + 2] == 'a' && ar[i + 3] == 0 && arg == 1) {
            return 1;
        } else if (ar[i] == '.' && ar[i + 1] == 'o' && ar[i + 2] == 0 && arg == 2) {
            return 1;
        }
    }
    return 0;
}

int get_memory(string line)
{
    // GETTING ADDRESS
    if ((int)line[0] < 48 || (int)line[1] < 48 || (int)line[0] > 57 || (int)line[1] > 57) {
        cout << " Wrong number of command" << endl;
        return 1;
    }
    int address = ((int)(line[0]) - 48) * 10 + (int)(line[1]) - 48;
    // GETTING COMMAND
    int command, i = 3;
    string temp;
    while (line[i] != ' ') {
        temp += line[i], i++;
    }
    command = get_command(temp);
    if (command == -1) {
        cout << " In line " << address << " wrong command!" << endl;
        return 1;
    }
    // GETTING OPERAND
    while (line[i] < '0' || line[i] > '9' || line[i] == ' ')
        i++;
    int operand = 0, count = 0;
    if (line[i] == '+')
        i++;
    while (line[i] != ' ' || line[i] != '\n' || line[i] != '\t' || (int)line[i] != 32) {
        if ((int)line[i] < 48 || (int)line[i] > 58) {
            break;
            cout << " Wrong operand!" << endl;
            return 1;
        }
        count++, i++;
    }

    i -= count, count--;
    while (count > -1) {
        operand += pow(10, count) * ((int)line[i] - 48);
        count--, i++;
    }
    if (command == 0) {
        sc_memorySet(address, operand);
    } else if (operand > 127) {
        return 1;
    } else {
        int value = 0;
        sc_commandEncode(command, operand, &value);
        sc_memorySet(address, value);
    }
    cout << "\t\t" << std::setfill('0') << std::setw(2) << address;
    cout << " 0x" << std::setfill('0') << std::setw(2) << std::hex << command << std::dec;
    cout << " " << std::setfill('0') << std::setw(2) << operand << endl;
    // //
    return 0;
}

// ./sat imf.sa ouf.o
void asm_to_simp(string in, string out)
{
    string line;
    std::ifstream inf(in, std::ios::binary);
    if (!inf.is_open()) {
        cout << "File " << in << " cannot be open" << endl;
        return;
    }
    sc_init();
    cout << endl;
    while (getline(inf, line)) {
        cout << line;
        if (get_memory(line)) {
            return;
        }
    }
    sc_memorySave(out);
    inf.close();
}