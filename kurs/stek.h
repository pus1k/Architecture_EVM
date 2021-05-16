#ifndef STEK_H
#define STEK_H

struct Stek {
    int operand = 0;
    int command = 0;
    int num = 0;
    struct Stek* next = NULL;
};
typedef struct Stek Stek;

Stek* _new(int num = 0, int command = 0, int operand = 0, Stek* next = NULL)
{
    Stek* temp = new Stek;
    temp->num = num;
    temp->command = command;
    temp->operand = operand;
    temp->next = next;
    return temp;
}
void add(Stek* head, Stek* node)
{
    if (head) {
        Stek* temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = node;
    }
}
void rem(Stek* head, Stek* node)
{
    if (head) {
        Stek* temp = head;
        while (temp->next != node && temp->next)
            temp = temp->next;
        temp->next = node->next;
    }
}
void pop(Stek** head)
{
    if (*head) {
        *head = (*head)->next;
    }
}
Stek* find(Stek* head, int value)
{
    if (head) {
        Stek* temp = head;
        while (temp->next) {
            if (temp->num == value) {
                return temp;
            }
            temp = temp->next;
        }
    }
    return NULL;
}
Stek* last(Stek* head)
{
    if (head) {
        Stek* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        return temp;
    }
    return NULL;
}
#endif