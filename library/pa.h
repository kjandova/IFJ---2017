#ifndef IFJ_PA_H
#define IFJ_PA_H

#include <stdbool.h>

int expeRetype(int typeA, int typeB);
unsigned int get_table_index(int flag);
bool is_handle(PAList *l);

typedef struct items{
    int id;
    bool is_terminal;
    bool E_handle;
    struct items *next;
    struct items *prev;
}PAItem;

typedef struct {
    PAItem *first;
    PAItem *last;
    PAItem *lastTerminal;
}PAList;

#endif //IFJ_PA_H
