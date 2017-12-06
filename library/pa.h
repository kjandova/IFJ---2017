///////////////////////////////////////////////////////////////////////////////////
//
//  @Project            IFJ 2017
//
//  @Authors
//  Kristýna Jandová    xjando04
//  Vilém Faigel        xfaige00
//  Nikola Timková      xtimko01
//  Bc. Václav Doležal  xdolez76
//
//  @File               pa.h
//  @Description
//
//
///////////////////////////////////////////////////////////////////////////////////

#ifndef IFJ_PA_H
#define IFJ_PA_H

#include <stdbool.h>


typedef struct items{
    int flag;
    string name;
    bool is_terminal;
    bool is_expression;
    bool is_startOfExpr;

    //toto je skarede ale bohuzial
    struct DIM * prem;
    struct items *next;
    struct items *prev;
}PAItem;



typedef struct PAList{
    PAItem *first;
    PAItem *last;
    PAItem *lastTerminal;
    PAItem *startExp;
}PAList;

int returnCommands(struct DIM * item1, struct DIM * item2, int flag);
//int prec_anal(struct DIM * _return);
void delete_list(PAList *a);
void init_list(PAList *l);
PAItem * last_terminal(PAList *l);

void insert_item(PAList *l, int flag, string name);



#endif //IFJ_PA_H
