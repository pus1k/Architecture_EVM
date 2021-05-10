#include "../lab2/simple_computer.h"
#include <iomanip>
#include <stdio.h>
#include <string.h>

char var[30];

typedef struct {
    int num = 0;
    int command = 0;
    int operand = 0;
} Result;

int get_command_basic(string line, int* ind)
{
    string command;
    for (int j = 0; isalpha(line[*ind]); (*ind)++, j++) {
        if (!isupper(line[*ind])) {
            printf("Error. Command must be in lowercase.");
            return -1;
        }
        command += line[*ind];
    }
    if (command == "REM") {
        return 0;
    } else if (command == "INPUT") {
        return 1;
    } else if (command == "OUTPUT") {
        return 2;
    } else if (command == "END") {
        return 3;
    } else if (command == "IF") {
        return 4;
    } else if (command == "LET") {
        return 5;
    } else if (command == "GOTO") {
        return 6;
    }
    return -1;
}
int get_num(string line, int* ind, int* num)
{
    int digit[5];
    while (line[*ind] != ' ' && line[*ind] != '\t' && line[*ind] != '\n') {
        if (isdigit(line[*ind])) {
            digit[*ind] = (int)line[*ind] - 48, (*ind)++;
        } else {
            return 1;
        }
    }
    *num = digit[0];
    for (int j = 1; j < *ind; j++) {
        *num += digit[j] * pow(10, j);
    }
    return 0;
}
int get_full_string(string line, Result* res)
{
    // GETTING NUMBER
    int ind = 0;
    if (get_num(line, &ind, &res->num)) {
        cout << "\nWrong number of command" << endl;
        return 1;
    }
    //
    ind++;
    if (!isalpha(line[ind])) {
        cout << "\nWrong spaceing between num and command!" << endl;
        return 1;
    }
    // GETTING COMMAND
    res->command = get_command_basic(line, &ind);
    if (res->command == -1) {
        cout << "\nWrong command" << endl;
        return 1;
    } else if (res->command == 1 && res->command == 2) {
        while (!isalpha(line[ind])) {
            ind++;
        }
        int i = 0;
        while (i < 30) {
            if (var[i] == 0 || var[i] == line[ind]) {
                var[i] = line[ind];
                break;
            }
            i++;
        }
    }
    return 0;
}
int translator(string from, string where)
{
    std::ifstream IN(from, std::ios::binary);
    if (!IN.is_open()) {
        cout << "File " << from << " cannot be open" << endl;
        return 1;
    }
    std::ofstream OUT(where, std::ios::binary);
    if (!OUT.is_open()) {
        cout << "File " << where << " cannot be open" << endl;
        return 1;
    }
    string line;
    Result* res = new Result;
    while (getline(IN, line)) {
        cout << line << endl;
        if (get_full_string(line, res)) {
            return 1;
        }
    }
    return 0;
}
int isOperation(char symbol)
{

    if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '(' || symbol == ')') {
        return 1;
    }

    return 0;
}
int main(int argc, char* argv[])
{
    string line;
    if (argc != 3) {
        perror("Incorrect arguments!\n");
        return 0;
    }
    sc_init();
    translator(argv[1], "basic.su");
    // asm_to_simp("basic.su", argv[2]);
    return 0;
}