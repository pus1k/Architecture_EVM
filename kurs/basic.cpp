#include "../lab2/simple_computer.h"
#include "asm.h"
#include "rpn.h"
#include "stek.h"
#include <iomanip>
#include <stdio.h>
#include <string.h>

int var[30];

int is_sp(char c)
{
    if ((c == ' ') || (c == '\t') || (c == '\0') || (c == '\n'))
        return 1;
    else
        return 0;
}
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
int get_num(string line, int* ind)
{
    int digit[5];
    int i = 0;
    while (!is_sp(line[*ind])) {
        if (isdigit(line[*ind])) {
            digit[i] = (int)line[*ind] - 48, (*ind)++, i++;
        } else {
            return -1;
        }
    }
    int num = digit[0];
    for (int j = 1; j < i; j++) {
        num += digit[j] * pow(10, j);
    }
    return num;
}
int get_full_string(Stek* head, string line)
{
    // GETTING NUMBER
    Stek* node = _new();
    int ind = 0;
    node->num = get_num(line, &ind) - 1;
    if (node->num == -1) {
        cout << "\nWrong number of command" << endl;
        return 1;
    }
    //
    ind++;
    if (!isalpha(line[ind])) {
        cout << "\nWrong spaceing between num and command! " << node->num << endl;
        return 1;
    }
    // GETTING COMMAND
    node->command = get_command_basic(line, &ind);
    if (node->command == -1) {
        cout << "\nWrong command" << endl;
        return 1;
    } else if (node->command != 0 && node->command != 3) {
        while (line[ind] == ' ' || line[ind] == '\t') {
            ind++;
        }
    }
    add(head, node);
    return ind;
}
int its_in_var(int a)
{
    for (int i = 0; i < 30; i++) {
        if (var[i] == a)
            return i;
        if (var[i] == 1) {
            var[i] = a;
            return i;
        }
    }
    return 30;
}
int get_len(string str)
{
    int i;
    for (i = 0; isdigit(str[i]); i++) {
    }
    return i + 3;
}

void rpn_to_basic(Stek* head, string rpn, int addr, int* additional_num)
{
    Stek* ptr = last(head);
    Rpn* arr = NULL;
    for (int i = 0; rpn[i] != '.'; i++) {
        if (rpn[i] == ',') {
            continue;
        }
        if (isalpha(rpn[i])) {
            int temp = its_in_var(rpn[i]);
            if (temp != 30) {
                arr = push(arr, 99 - temp);
            }
        } else if ((rpn[i] == '+') || (rpn[i] == '-') || (rpn[i] == '*') || (rpn[i] == '/')) {
            if (arr->next) {
                int num = 0;
                if (ptr->command == 5) {
                    int first = (int)stack_pop(&arr);
                    int second = (int)stack_pop(&(arr->next));
                    ptr->command = 0x20, ptr->operand = first;
                    Stek* node1 = _new(ptr->num + 1, 0x21, addr);
                    Stek* node2 = _new(node1->num + 1);
                    ptr->next = node1, node1->next = node2;
                    if (rpn[i] == '+') {
                        node2->command = 0x30;
                    } else if (rpn[i] == '-') {
                        node2->command = 0x31;
                    } else if (rpn[i] == '*') {
                        node2->command = 0x32;
                    } else if (rpn[i] == '/') {
                        node2->command = 0x33;
                    }
                    num = node2->num + 1;
                    node2->operand = second;
                } else {
                    int first = stack_pop(&arr);
                    int second = stack_pop(&arr->next);
                    Stek* node1 = _new(ptr->num + 1, 0x20, first);
                    Stek* node2 = _new(node1->num + 1, 0x21, addr);
                    Stek* node3 = _new(node2->num + 1);
                    ptr->next = node1, node1->next = node2, node2->next = node3;
                    if (rpn[i] == '+') {
                        node3->command = 0x30;
                    } else if (rpn[i] == '-') {
                        node3->command = 0x31;
                    } else if (rpn[i] == '*') {
                        node3->command = 0x32;
                    } else if (rpn[i] == '/') {
                        node3->command = 0x33;
                    }
                    node3->operand = second;
                    num = node3->num + 1;
                }
                Stek* node4 = _new(num, 0x21, addr);
                ptr->next = node4;
                ptr = last(head);
            }
        }
    }
}
void to_asm(Stek* head, string where)
{
    std::ofstream OUT(where, std::ios::binary);
    if (!OUT.is_open()) {
        cout << "File " << where << " cannot be open" << endl;
        return;
    }
    string command;
    while (head) {
        if (head->command != 0) {
            if (head->command == 0x10)
                command = "READ  ";
            else if (head->command == 0x11)
                command = "WRITE ";
            else if (head->command == 0x20)
                command = "LOAD  ";
            else if (head->command == 0x21)
                command = "STORE ";
            else if (head->command == 0x30)
                command = "ADD   ";
            else if (head->command == 0x31)
                command = "SUB   ";
            else if (head->command == 0x32)
                command = "DIVIDE";
            else if (head->command == 0x33)
                command = "MUL   ";
            else if (head->command == 0x40)
                command = "JUMP  ";
            else if (head->command == 0x41)
                command = "JNEG  ";
            else if (head->command == 0x42)
                command = "JZ    ";
            else if (head->command == 0x43)
                command = "HALT  ";
            else if (head->command == 0x63)
                command = "RCR   ";
            OUT << std::setfill('0') << std::setw(2) << head->num - 1 << ' ' << command << head->operand << ' '
                << "\n";
            // cout << std::setfill('0') << std::setw(2) << head->num - 1 << " " << command << head->operand << endl;
        }
        head = head->next;
    }
}
int translator(string from, string where)
{
    std::ifstream IN(from, std::ios::binary);
    if (!IN.is_open()) {
        cout << "File " << from << " cannot be open" << endl;
        return 1;
    }
    string line;
    Stek* head = _new();
    Stek* node;
    int ind = 0;
    int additional_num = 0;
    while (getline(IN, line)) {
        // cout << line << endl;
        if ((ind = get_full_string(head, line)) == 1) {
            return 1;
        }
        string oper = "";
        int bib = ind;
        while (line[bib] != '\0' && line[bib] != '\n') {
            oper += line[bib], bib++;
        }
        node = last(head);
        node->num += additional_num;
        if (node->command == 0 || node->command == 3) {
            if (node->command == 3) {
                node->command = 0x43;
            }
            continue;
        }
        if (node->command == 1 || node->command == 2) {
            int operand = its_in_var((int)oper[0]);
            if (operand == 30) {
                cout << "\nSomething wrong with operand!" << endl;
                return 1;
            }
            if (var[operand] == 1)
                var[operand] = (int)oper[0];
            node->operand = 99 - operand;
            if (node->command == 1) {
                node->command = 0x10;
            } else {
                node->command = 0x11;
            }
        } else if (node->command == 4) {
            int operand[2];
            int len = 4, num = 0;
            for (int i = 0; i < 2; i++) {
                if (isdigit(oper[i * len])) {
                    num = get_num(oper, &len);
                    if (!i)
                        len += 4;
                    operand[i] = its_in_var((-1) * num);
                } else {
                    operand[i] = its_in_var((int)oper[i * len]);
                }
                if (operand[i] == 30) {
                    cout << "\nSomething wrong with operand!" << endl;
                    return 1;
                }
            }
            node->command = 0x20;
            Stek* node2 = _new(node->num + 1, 0x31);
            Stek* node3 = _new(node2->num + 1);
            Stek* node4 = _new(node3->num + 1, 0x40);
            additional_num += 3;
            if (oper[2] == '=') {
                node->operand = 99 - operand[0], node->next = node2;
                node2->operand = 99 - operand[1], node2->next = node3;
                node3->command = 0x42, node3->operand = node3->num + 1, node3->next = node4;
            } else if (oper[2] == '>') {
                node->operand = 99 - operand[1], node->next = node2;
                node2->operand = 99 - operand[0], node2->next = node3;
                node3->command = 0x41, node3->operand = node3->num + 1, node3->next = node4;
            } else if (oper[2] == '<') {
                node->operand = 99 - operand[0], node->next = node2;
                node2->operand = 99 - operand[1], node2->next = node3;
                node3->command = 0x41, node3->operand = node3->num + 1, node3->next = node4;
            } else {
                cout << "Wrong sign in if!" << endl;
                return 1;
            }
            len++;
            if (is_sp(oper[len])) {
                return 1;
            }
            string GOTO;
            while (!is_sp(oper[len]))
                GOTO += oper[len], len++;
            if (GOTO != "GOTO") {
                return 1;
            }
            len++;
            node4->operand = get_num(oper, &len);
        } else if (node->command == 5) {
            if (!isalpha(oper[0])) {
                cout << "In len arg is not num!" << endl;
                return 1;
            }
            int addr = its_in_var(oper[0]);
            if (addr == 30) {
                return 1;
            }
            string rpn;
            int j = 1;
            while (oper[j] != '\0' && oper[j] != '\n') {
                rpn += oper[j], j++;
            }
            string rpn_basic;
            translate_to_rpn(rpn, &rpn_basic);
            // cout << rpn_basic << endl;
            rpn_to_basic(head, rpn_basic, 99 - addr, &additional_num);
        }
    }
    pop(&head);
    // while (head) {
    //     cout << head->num << " " << head->command << " " << head->operand << endl;
    //     head = head->next;
    // }
    to_asm(head, where);
    return 0;
}

int main(int argc, char* argv[])
{
    string line;
    if (argc != 3) {
        cout << "Incorrect arguments!" << endl;
        return 0;
    }
    for (int i = 0; i < 30; i++) {
        var[i] = 1;
    }
    translator(argv[1], "basic.o");
    sc_init();
    asm_to_simp("basic.o", argv[2]);
    return 0;
}