#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "pa.h"

// //////////////////////////////////////////////////////


void init_list(PAList *l) {
    l->first = NULL;
    l->last = NULL;
    l->lastTerminal = NULL;
}

void insert_item(PAList *l, int flag, string name) {


    if (l->first == NULL) {


        PAItem *tmp;
        tmp = malloc(sizeof(PAItem));
        tmp->is_terminal = true;
        tmp->is_expression = false;
        tmp->is_startOfExpr = false;
        tmp->next = NULL;

        tmp->flag = flag;
        tmp->name = name;

        tmp->prev = l->last;
        l->last = tmp;

    } else {


        PAItem *tmp;
        tmp = malloc(sizeof(PAItem));
        tmp->is_terminal = true;
        tmp->is_expression = false;
        tmp->is_startOfExpr = false;

        tmp->flag= flag;
        tmp->name = name;

        tmp->next = l->last->next;
        l->last->next->prev = tmp;
    }
}


PAItem * last_terminal(PAList *l) {
  PAItem *tmp = l->last;
  while (tmp->is_terminal == false) {
    tmp = tmp->prev;
  }
  l->lastTerminal = tmp;
  return tmp;
}

bool is_expression(PAList *l) {
    PAItem *tmp = l->last;

    while (tmp) {
        if (tmp->is_expression == true)
            return true;
        tmp = tmp->prev;
    }

    return false;
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
/*  $  */ {'<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', ' ', '<', 'E',},
};

unsigned int getTableIndex(int flag) {
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
        case TOKEN_STRING:
        case TOKEN_ID:                      return 13;  // i
        case TOKEN_END_OF_LINE:             return 14;  // $
    }

    return ERROR_INTERN;
}

char getTable(int i, int j) {
    return PATable[getTableIndex(i)][getTableIndex(j)];
}

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



void printList(PAList * a){
    PAItem *tmp = a->last;
        while(tmp->prev != NULL){
        
            tmp = tmp->prev;
            printf("Name: %s, Flag: %d, Is terminal: %d, Is expr: %d Is startE: %d\n", tmp->name.str, tmp->flag, tmp->is_terminal, tmp->is_expression, tmp->is_startOfExpr);
        }
        free(tmp);
}



void prec_anal(){


    scanner_init("./tests/Scanner/Test_1.bas");
    Token b;
    
    PAList *a = malloc(sizeof(PAList));        //zasobnik - os y v tabulke
    init_list(a);



    //vlozi na spodok listu $
    string end;    
    end.str = "$";
    insert_item(a, TOKEN_END_OF_LINE, end);

    a->lastTerminal = a->last;

     
    b = scanner_next_token();           

   

    while (!((b.flag == TOKEN_END_OF_LINE) && (a->lastTerminal->flag == TOKEN_END_OF_LINE))){ 


        //b = scanner_next_token();
        
        unsigned int j = getTableIndex(b.flag);


        //najde posledny terminal s kt. bude porovnavat znak na vstupe
        PAItem * lastTerminal = a->last;
            while (lastTerminal->is_terminal == false) {
            lastTerminal = lastTerminal->prev;
        }
        a->lastTerminal = lastTerminal;

        

        unsigned int i = getTableIndex(lastTerminal->flag);




        char precedence = PATable[i][j];

        switch(precedence){
            case '=':

                insert_item(a, b.flag, b.ID);
                b = scanner_next_token();

                

                break;

            case '<':

                insert_item(a, b.flag, b.ID);
                b = scanner_next_token();



                
                if(a->last->flag == TOKEN_ID || a->last->flag == TOKEN_INTEGER ||
                    a->last->flag == TOKEN_DOUBLE || a->last->flag == TOKEN_STRING){
                        a->last->is_startOfExpr = true;
                        a->last->is_expression = true;
                        a->last->is_terminal = true;
                }

                //nie je pravidlo, vloz na koniec listu
                else{
                    a->last->is_startOfExpr = false;
                    a->last->is_terminal = true;
                    a->last->is_expression = true;
                    a->last->prev->is_startOfExpr = true;
                }
                

                break;

            case '>':


                //pravidlo E -> E
                if(a->lastTerminal->is_startOfExpr == true){
                    a->lastTerminal->is_expression = true;
                    a->lastTerminal->is_terminal = false;
                    a->lastTerminal->is_startOfExpr = false;
                   // printf("E-> %s \n", a->lastTerminal->name.str);

                }

                //pravidlo E -> E x E
                else{
                            PAItem *startExp = a->last;
                            while (startExp->is_startOfExpr == false) {
                                startExp = startExp->prev;
                            }
     
                            a->startExp = startExp;


                    //*******tu predat vyslednu operaciu*******
                    printf("%s = %s %s %s\n", a->startExp->name.str, a->startExp->name.str, getTokenName(a->lastTerminal->flag), a->last->name.str);
                    

                    // TODO: a->startExp = expeRetype()

                   


                    free(a->last);
                    free(a->lastTerminal);
                    PAItem * tmp;
                    tmp = startExp;
                    a->last = tmp;

                    a->last->is_terminal = false;
                    a->last->is_expression = true;
                    a->last->is_startOfExpr = false;
                }
               

                break;

            case 'E':

                //koniec, $ == $
                printf("Successfull end.\n");
                break;




            default:

                //nie je to ani jedna z veci z tabulky?
                printf("error\n");
                break;
        }
 
    if (precedence == ' '){
        break;
    }

    }
        
   

    free(a);


}
