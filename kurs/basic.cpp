#include "../lab2/simple_computer.h"
#include "asm.h"
#include "rpn.h"
#include "stek.h"
#include <iomanip>
#include <stdio.h>
#include <string.h>

int var[30];
Stek* constant = _new();

int is_sp(char c)
{
    if ((c == ' ') || (c == '\t') || (c == '\0') || (c == '\n') || (c == ',') || (c == '.'))
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

int find_command_for_GOTO(Stek* head, int addr)
{
    if (head) {
        Stek* ptr = head;
        while (ptr) {
            if (ptr->step == addr)
                return ptr->num;
            ptr = ptr->next;
        }
    }
    return -1;
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
                arr = push(arr, (char)(99 - temp));
            }
        } else if (isdigit(rpn[i])) {
            int value = get_num(rpn, &i);
            int temp = its_in_var((-1) * value);
            if (temp != 30) {
                if (var[temp] == 1) {
                    var[temp] = (-1) * value;
                    Stek* const1 = _new(99 - temp, value, 0);
                    add(constant, const1);
                }
                arr = push(arr, (char)(99 - temp));
            }
        } else if ((rpn[i] == '+') || (rpn[i] == '-') || (rpn[i] == '*') || (rpn[i] == '/')) {
            if (arr->next) {
                int num = 0;
                int first = stack_pop(&arr);
                int second = stack_pop(&arr);
                if (ptr->command == 5) {
                    ptr->command = 0x20, ptr->operand = second;
                    Stek* node2 = _new(ptr->num + 1);
                    ptr->next = node2;
                    if (rpn[i] == '+') {
                        node2->command = 0x30;
                    } else if (rpn[i] == '-') {
                        node2->command = 0x31;
                    } else if (rpn[i] == '/') {
                        node2->command = 0x32;
                    } else if (rpn[i] == '*') {
                        node2->command = 0x33;
                    }
                    num = node2->num + 1;
                    node2->operand = first;
                    (*additional_num) += 2;
                } else {
                    Stek* node1 = _new(ptr->num + 1, 0x20, second);
                    Stek* node3 = _new(node1->num + 1);
                    ptr->next = node1, node1->next = node3;
                    if (rpn[i] == '+') {
                        node3->command = 0x30;
                    } else if (rpn[i] == '-') {
                        node3->command = 0x31;
                    } else if (rpn[i] == '*') {
                        node3->command = 0x32;
                    } else if (rpn[i] == '/') {
                        node3->command = 0x33;
                    }
                    num = node3->num + 1;
                    node3->operand = first;
                    (*additional_num) += 3;
                }
                ptr = last(head);
                Stek* node4 = _new(num, 0x21, addr);
                ptr->next = node4;
                ptr = ptr->next;
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
                command = "READ   ";
            else if (head->command == 0x11)
                command = "WRITE  ";
            else if (head->command == 0x20)
                command = "LOAD   ";
            else if (head->command == 0x21)
                command = "STORE  ";
            else if (head->command == 0x30)
                command = "ADD    ";
            else if (head->command == 0x31)
                command = "SUB    ";
            else if (head->command == 0x32)
                command = "DIVIDE ";
            else if (head->command == 0x33)
                command = "MUL    ";
            else if (head->command == 0x40)
                command = "JUMP   ";
            else if (head->command == 0x41)
                command = "JNEG   ";
            else if (head->command == 0x42)
                command = "JZ     ";
            else if (head->command == 0x43)
                command = "HALT   ";
            else if (head->command == 0x63)
                command = "RCR    ";
            else if (head->command == -1) {
                command = "=     +";
                OUT << std::setfill('0') << std::setw(2) << head->num << ' ' << command << head->operand << ' ' << endl;
                // cout << std::setfill('0') << std::setw(2) << head->num << " " << command << head->operand << endl;
                head = head->next;
                continue;
            }
            OUT << std::setfill('0') << std::setw(2) << head->num << ' ' << command << std::setfill('0') << std::setw(2) << head->operand << ' ' << endl;
            // cout << std::setfill('0') << std::setw(2) << head->num << " " << command << std::setfill('0') << std::setw(2) << head->operand << endl;
        }
        head = head->next;
    }
    while (constant) {
        OUT << std::setfill('0') << std::setw(2) << constant->num << ' ' << "=     +" << constant->command << ' ' << endl;
        constant = constant->next;
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
        if ((ind = get_full_string(head, line)) == 1) {
            return 1;
        }
        string oper = "";
        int bib = ind;
        while (line[bib] != '\0' && line[bib] != '\n') {
            oper += line[bib], bib++;
        }
        node = last(head);
        node->step = node->num;
        node->num += additional_num;
        if (node->command == 0 || node->command == 3) {
            if (node->command == 3) {
                node->command = 0x43;
            }
            if (node->command == 0) {
                rem(head, node);
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
            int len = 0, num = 0;

            for (int i = 0; i < 2; i++) {
                if (isdigit(oper[i * len])) {
                    num = get_num(oper, &len);
                    operand[i] = its_in_var((-1) * num);
                    if (!i)
                        len += 3;
                    if (i)
                        len--;
                } else {
                    operand[i] = its_in_var((int)oper[i * len]);
                    if (!i)
                        len = 4;
                    else
                        len++;
                }
                if (operand[i] == 30) {
                    cout << "\nSomething wrong with operand!" << endl;
                    return 1;
                }
                if (var[operand[i]] == 1) {
                    if (isdigit(oper[i * len])) {
                        var[operand[i]] = (-1) * num;
                        Stek* const1 = _new(99 - operand[i], num, 0);
                        add(constant, const1);
                        len++;
                    } else {
                        var[operand[i]] = oper[i * len];
                        Stek* node_temp = _new(node->num, node->command, node->operand, node->next);
                        Stek* node1 = _new(node->num, 0x10, 99 - operand[i]);
                        rem(head, node);
                        node = last(head);
                        node->next = node1, node1->next = node_temp;
                        additional_num++;
                        node = last(head);
                        node->num++;
                    }
                }
            }
            len++;
            if (is_sp(oper[len])) {
                cout << oper << endl;
                return 1;
            }
            string GOTO;
            while (!is_sp(oper[len]))
                GOTO += oper[len], len++;
            if (GOTO != "GOTO") {
                return 1;
            }
            len++;
            int addr = get_num(oper, &len) - 1;
            addr = find_command_for_GOTO(head, addr);
            if (addr == -1) {
                cout << "This addr in GOTO is WRONG" << endl;
                return 1;
            }
            node->command = 0x20;
            Stek* node2 = _new(node->num + 1, 0x31);
            Stek* node3 = _new(node2->num + 1);
            additional_num += 2;
            if (oper[2] == '=') {
                node->operand = 99 - operand[0], node->next = node2;
                node2->operand = 99 - operand[1], node2->next = node3;
                node3->command = 0x42;
            } else if (oper[2] == '>') {
                node->operand = 99 - operand[1], node->next = node2;
                node2->operand = 99 - operand[0], node2->next = node3;
                node3->command = 0x41;
            } else if (oper[2] == '<') {
                node->operand = 99 - operand[0], node->next = node2;
                node2->operand = 99 - operand[1], node2->next = node3;
                node3->command = 0x41;
            } else {
                cout << "Wrong sign in if!" << endl;
                return 1;
            }
            node3->operand = addr;
        } else if (node->command == 5) {
            if (!isalpha(oper[0])) {
                cout << "In let arg is not num!" << endl;
                return 1;
            }
            int addr = its_in_var(oper[0]);
            if (addr == 30) {
                return 1;
            }
            string rpn;
            int j = 4;
            while (oper[j] != '\0' && oper[j] != '\n') {
                rpn += oper[j], j++;
            }
            j = 0;
            var[addr] = oper[0];
            if (isdigit(rpn[0])) {
                int one_value = get_num(rpn, &j);
                if (rpn[j] == '\0' || rpn[j] == '\n') {
                    int one_ind = its_in_var(-1 * one_value);
                    if (one_ind != 30) {
                        if (var[one_ind] == 1) {
                            var[one_ind] = (-1) * one_value;
                            Stek* const1 = _new(99 - one_ind, one_value, 0);
                            add(constant, const1);
                        }
                        node->command = 0x20, node->operand = 99 - one_ind;
                        Stek* node1 = _new(node->num + 1, 0x21, 99 - addr);
                        node->next = node1;
                        additional_num++;
                    }
                } else {
                    string rpn_basic;
                    translate_to_rpn(rpn, &rpn_basic);
                    rpn_to_basic(head, rpn_basic, 99 - addr, &additional_num);
                }
            } else if (isalpha(rpn[0])) {
                if (rpn[1] == '\0' || rpn[1] == '\n') {
                    int one_ind = its_in_var(rpn[0]);
                    node->command = 0x20, node->operand = 99 - one_ind;
                    Stek* node1 = _new(node->num + 1, 0x21, 99 - addr);
                    node->next = node1;
                    additional_num++;
                } else {
                    string rpn_basic;
                    translate_to_rpn(rpn, &rpn_basic);
                    rpn_to_basic(head, rpn_basic, 99 - addr, &additional_num);
                }
            } else {
                string rpn_basic;
                translate_to_rpn(rpn, &rpn_basic);
                rpn_to_basic(head, rpn_basic, 99 - addr, &additional_num);
            }
        }
    }
    pop(&head);
    pop(&constant);
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
    translator(argv[1], "load/basic.su");
    sc_init();
    asm_to_simp("load/basic.su", argv[2]);
    return 0;
}