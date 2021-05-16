#ifndef RPN_H
#define RPN_H

struct Rpn {
    char c;
    struct Rpn* next;
};
typedef struct Rpn Rpn;

Rpn* push(Rpn* head, char a)
{
    Rpn* temp = new Rpn;
    if (temp) {
        temp->c = a;
        temp->next = head;
        return temp;
    }
    return NULL;
}
char stack_pop(Rpn** head)
{
    if (*head) {
        Rpn* ptr = (*head)->next;
        char a = (*head)->c;
        delete (*head);
        *head = ptr;
        return a;
    }
    return '\0';
}
int get_prior(char c)
{
    if (c == '*' || c == '/')
        return 3;
    if (c == '-' || c == '+')
        return 2;
    if (c == '(')
        return 1;
    return 0;
}
void translate_to_rpn(string str, string* out)
{
    Rpn* opers = NULL;

    for (int i = 0; str[i] != '\0' && str[i] != '\n'; i++) {
        if (str[i] == ' ' || str[i] == '\t') {
            continue;
        } else if (str[i] == ')') {
            while (opers->c != '(')
                (*out) += stack_pop(&opers), (*out) += ",";
            stack_pop(&opers), (*out) += ",";
        } else if (isalpha(str[i])) {
            (*out) += str[i], (*out) += ",";
        } else if (isdigit(str[i])) {
            while (isdigit(str[i])) {
                (*out) += str[i];
                i++;
            }
            (*out) += ",";
        } else if (str[i] == '(') {
            opers = push(opers, str[i]);
        } else if (str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*') {
            if (opers == NULL) {
                opers = push(opers, str[i]);
            } else if (get_prior(opers->c) < get_prior(str[i])) {
                opers = push(opers, str[i]);
            } else {
                while ((opers != NULL) && (get_prior(opers->c) >= get_prior(str[i])))
                    (*out) += stack_pop(&opers), (*out) += ",";
                opers = push(opers, str[i]);
            }
        }
    }
    while (opers != NULL) {
        (*out) += stack_pop(&opers);
        if (opers)
            (*out) += ",";
    }
    (*out) += ".";
}
#endif