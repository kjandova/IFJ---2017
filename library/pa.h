#ifndef IFJ_PA_H
#define IFJ_PA_H

#include <stdbool.h>


typedef struct items{
    int flag;
    string name;
    bool is_terminal;
    bool is_expression;
    bool is_startOfExpr;
    struct items *next;
    struct items *prev;
}PAItem;



typedef struct PAList{
    PAItem *first;
    PAItem *last;
    PAItem *lastTerminal;
    PAItem *startExp;
}PAList;


void prec_anal();
void init_list(PAList *l);
PAItem * last_terminal(PAList *l);

bool is_expression(PAList *l);
void insert_item(PAList *l, int flag, string name);



#endif //IFJ_PA_H
