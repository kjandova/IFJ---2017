#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mem.h>
#include "pa.h"

// //////////////////////////////////////////////////////


void init_list(PAList *l) {
    l->first = NULL;
    l->last = NULL;
    l->lastTerminal = NULL;
}

void insert_handle(PAList *l) {


    if (l->last == l->lastTerminal) {


        PAItem *tmp;
        tmp = malloc(sizeof(PAItem));
        tmp->is_terminal = false;
        tmp->E_handle = true;
        tmp->next = NULL;
        tmp->prev = l->last;
        l->last = tmp;


    } else {


        PAItem *tmp;
        tmp = malloc(sizeof(PAItem));
        tmp->is_terminal = false;
        tmp->E_handle = true;
        tmp->next = l->lastTerminal->next;
        l->lastTerminal->next->prev = tmp;
        tmp->prev = l->lastTerminal;
    }
}

bool is_handle(PAList *l) {
    PAItem *tmp = l->last;

    while (tmp) {
        if (tmp->e_handle == true)
            return true;
        tmp = tmp->prev;
    }

    return false;
}


unsigned int get_table_index(int flag) {
    switch(flag) {
        case TOKEN_ADD:                     return 0;   // +
        case TOKEN_SUB:                     return 1;   // -
        case TOKEN_MUL:                     return 2;   // *
        case TOKEN_DIV:                     return 3;   // /
        case TOKEN_BACKSLASH:               return 4;   // '\'
        case TOKEN_MORE:                    return 5;   // >
        case TOKEN_LESS:                    return 6;   // <
        case TOKEN_MORE_OR_EQUAL:           return 7;   // >=
        case TOKEN_LESS_OR_EQUAL:           return 8;   // <=
        case TOKEN_EQUALS:                  return 9;   // =
        case TOKEN_NON_EQUAL:               return 10;  // <>
        case TOKEN_BRACKET_LEFT:            return 11;  // (
        case TOKEN_BRACKET_RIGHT:           return 12;  // )
        case TOKEN_INTEGER:
        case TOKEN_DOUBLE:
        case TOKEN_STRING:                  return 13;  // i
        case TOKEN_END_OF_LINE:             return 14;  // $
    }

    return ERROR_INTERN;
}

const char PATable [15][15] = {
/*          +    -    *    /    \    >    <   >=    <=   =    <>   (    )    i    $       */
/*  +  */ {'>', '>', '<', '<', '<', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>',},
/*  -  */ {'>', '>', '<', '<', '<', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>',},
/*  *  */ {'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>',},
/*  /  */ {'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>',},
/*  \  */ {'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '<', '>',},
/*  >  */ {'<', '<', '<', '<', '<', ' ', ' ', ' ', ' ', ' ', ' ', '<', '>', '<', '>',},
/*  <  */ {'<', '<', '<', '<', '<', ' ', ' ', ' ', ' ', ' ', ' ', '<', '>', '<', '>',},
/*  >= */ {'<', '<', '<', '<', '<', ' ', ' ', ' ', ' ', ' ', ' ', '<', '>', '<', '>',},
/*  <= */ {'<', '<', '<', '<', '<', ' ', ' ', ' ', ' ', ' ', ' ', '<', '>', '<', '>',},
/*  =  */ {'<', '<', '<', '<', '<', ' ', ' ', ' ', ' ', ' ', ' ', '<', '>', '<', '>',},
/*  <> */ {'<', '<', '<', '<', '<', ' ', ' ', ' ', ' ', ' ', ' ', '<', '>', '<', '>',},
/*  (  */ {'<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '=', '<', ' ',},
/*  )  */ {'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', ' ', '>', ' ', '>',},
/*  i  */ {'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', ' ', '>', ' ', '>',},
/*  $  */ {'<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', ' ', '<', ' ',},
};

int expeRetype(int typeA, int typeB) {

    switch (typeA) {
        case DATA_TYPE_INT:
            switch (typeB) {
                case DATA_TYPE_INT:
                    return DATA_TYPE_INT;

                case DATA_TYPE_DOUBLE:
                    return DATA_TYPE_DOUBLE;
            }
            break;

        case DATA_TYPE_DOUBLE:
            switch (typeB) {
                case DATA_TYPE_DOUBLE:
                    return DATA_TYPE_DOUBLE;

                case DATA_TYPE_INT:
                    return DATA_TYPE_DOUBLE;
            }
            break;

        case DATA_TYPE_STRING:
            switch (typeB) {
                case DATA_TYPE_STRING:
                    return DATA_TYPE_STRING;
            }
            break;
    }

    return 0;
}



void prec_anal(){

    Token b;
    PAList * a;
    a = malloc(sizeof(PAList));        //zasobnik - os y v tabulke
    init_list(a);

    a->last->id = TOKEN_END_OF_LINE;
    b = scanner_next_token();

/*

    //pokial sa nedostanem na koniec vyrazu a zaroven na stacku nezostane iba $
    //while(((b = scanner_next_token()) != EOL) && (stack_peek(a) != T_END)) {

    while((b.flag != TOKEN_END_OF_LINE) && (stackTop(a) != TOKEN_END_OF_LINE)) {



        int j = get_table_index(b.flag);      //nacita index vstupneho tokenu
        int i = stackTop(a);
        char precedence = PATable[i][j];

        int e_counter = -1;

        switch(precedence){


            case '=':
                stackPush(a, b.ID);
                b = scanner_next_token();
                break;

            case '<':

                if (j == 13) {     //ak je vstupny znak identifikator, pravidlo E->i
                    e_counter++;
                    stackPush(a, b.ID);
                    b = scanner_next_token();


                }
                else{
                    stackPush(a, b.ID);
                    b = scanner_next_token();
                }
                break;


            case '>':
                //pravidla E -> E op E



/*
                if (strcmp(operators[operators_count], "+") == 0) {
                    printf("ADD %s %s %s", operators[operators_count - 1], operators[operators_count],
                           operators[operators_count - 1]);
                    operators_count--;
                    e[e_count]--;
                }


                if (strcmp(operators[operators_count], "-") == 0) {
                    printf("SUB %s %s %s", operators[operators_count - 1], operators[operators_count],
                           operators[operators_count - 1]);
                    operators_count--;
                }

                if (strcmp(operators[operators_count], "*") == 0) {
                    printf("MUL %s %s %s", operators[operators_count - 1], operators[operators_count],
                           operators[operators_count - 1]);
                    operators_count--;
                }

                if (strcmp(operators[operators_count], "/") == 0){
                        printf("DIV %s %s %s", operators[operators_count-1], operators[operators_count], operators[operators_count-1]);
                        operators_count--;
                }
                else printf("error");
                break;

            default:

                stack_clean(&a);
                printf("Expression syntax error");
                //ErrorException(ERROR_SYNTAX, "Expression syntax error");
                break;
        }

    }*/

}
