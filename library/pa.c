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
//  @File               pa.c
//  @Description
//
//
///////////////////////////////////////////////////////////////////////////////////

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

        if ((tmp = malloc(sizeof(PAItem))) == NULL){
            ErrorException(ERROR_INTERN, "Internal variable allocation failed.");
        }

        tmp->is_terminal = true;
        tmp->is_expression = false;
        tmp->is_startOfExpr = false;
        tmp->next = NULL;

        tmp->flag = flag;
        tmp->name = name;

        tmp->prev = NULL;
        tmp->next = NULL;
        l->last = tmp;
        l->first = tmp;

    } else {


        PAItem *tmp;

        if ((tmp = malloc(sizeof(PAItem))) == NULL){
            ErrorException(ERROR_INTERN, "Internal variable allocation failed.");
        }
        tmp->is_terminal = true;
        tmp->is_expression = false;
        tmp->is_startOfExpr = false;

        tmp->flag = flag;
        tmp->name = name;

        tmp->next = NULL;
        tmp->prev = l->last;
        l->last->next = tmp;
        l->last = tmp;
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

void delete_list(PAList *a){

  PAItem *tmp = a->last;

  if (tmp != NULL) {
    while (tmp->prev != NULL) {
      tmp = tmp->prev;
      free(tmp->prev);
    }
    free(tmp);
  }
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
/*  (  */ {'<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '=', '<', '>',},
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
        case DATA_TYPE_DOUBLE:
        case DATA_TYPE_STRING:
        case TOKEN_ID:                      return 13;  // i
        case TOKEN_END_OF_LINE:
        case TOKEN_THEN:                    return 14;  // $
    }

    return ERROR_INTERN;
}

char getTable(int i, int j) {
    return PATable[getTableIndex(i)][getTableIndex(j)];
}

int expeRetype(int typeA, int typeB) {

    switch (typeA) {
        case TOKEN_INTEGER:
            switch (typeB) {
                case TOKEN_INTEGER:
                    return TOKEN_INTEGER;

                case DATA_TYPE_DOUBLE:
                    return DATA_TYPE_DOUBLE;
            }
            break;

        case DATA_TYPE_DOUBLE:
            switch (typeB) {
                case DATA_TYPE_DOUBLE:
                    return DATA_TYPE_DOUBLE;

                case TOKEN_INTEGER:
                    return DATA_TYPE_DOUBLE;
            }
            break;

        case DATA_TYPE_STRING:
            switch (typeB) {
                case DATA_TYPE_STRING:
                    return DATA_TYPE_STRING;
            }
            break;

         //toto neskor zmazat   
        case TOKEN_ID:
            switch (typeB) {
                case TOKEN_ID:
                    return TOKEN_ID;
            }
            break;
    }

    return 0;
}

/*
*   @function      prec_anal
*   @param         struct Statment * s
*   @param         DIM * _return
*/
            
int prec_anal(){

    //
    //
    // dummy vstupny parameter
    //
    //

    string vysledok;
    vysledok.str = "vysledok";

    struct DIM * _return = malloc(sizeof(struct DIM));
    _return->dataType = DATA_TYPE_DOUBLE;
    _return->frame = FRAME_LOCAL;
    _return->name =  vysledok;



    //dummy premenna prem1
    string variable;
    variable.str = "variable";

    struct DIM * _prem1 = malloc(sizeof(struct DIM));
    _prem1->dataType = DATA_TYPE_DOUBLE;
    _prem1->frame = FRAME_LOCAL;
    _prem1->name =  variable;
    _prem1->valueDouble = 5.2;


    //dummy premenna prem2
    string beta;
    beta.str = "beta";

    struct DIM * _prem2 = malloc(sizeof(struct DIM));
    _prem2->dataType = DATA_TYPE_INT;
    _prem2->frame = FRAME_LOCAL;
    _prem2->name =  beta;
    _prem2->valueInteger = 1;

    //dummy premenna prem3
    string alpha;
    vysledok.str = "alpha";

    struct DIM * _prem3 = malloc(sizeof(struct DIM));
    _prem3->dataType = DATA_TYPE_DOUBLE;
    _prem3->frame = FRAME_LOCAL;
    _prem3->name =  alpha;
    _prem3->valueDouble = 5.0;






    //
    //
    // Precedencna analyza
    //
    //

    scanner_init("./tests/PA/Test_1.bas");
    Token b;
    
    PAList *a = malloc(sizeof(PAList));        //zasobnik - os y v tabulke
    init_list(a);



    //vlozi na spodok listu $ a spravi ho terminalom
    string end;    
    end.str = "$";
    insert_item(a, TOKEN_END_OF_LINE, end);
    a->lastTerminal = a->last;
    a->last->is_terminal = true;


    b = scanner_next_token();           

    int run = 0;








    while (!((b.flag == TOKEN_END_OF_LINE) && (a->lastTerminal->flag == TOKEN_END_OF_LINE))){ 


        unsigned int j = getTableIndex(b.flag);


        //najde posledny terminal s kt. bude porovnavat znak na vstupe
        PAItem * lastTerminal = last_terminal(a);
        a->lastTerminal = lastTerminal;

        

        unsigned int i = getTableIndex(lastTerminal->flag);
        char precedence = PATable[i][j];

        run++;


        switch(precedence){
 


            case '=':

                insert_item(a, b.flag, b.ID);
                b = scanner_next_token();
                break;



            case '<':

                insert_item(a, b.flag, b.ID);
                b = scanner_next_token();




                a->last->is_terminal = false;



                //ak je vo vyraze ciste iba jedna premenna
                if((run == 1) && (b.flag == TOKEN_END_OF_LINE)){
                    printf("E-> %s\n", a->last->name.str);
                    return SUCCESS;
                }


                if((isTokenID(a->last->flag)) || a->last->flag == TOKEN_INTEGER){
                        a->last->is_startOfExpr = true;
                        a->last->is_expression = true;
                        a->last->is_terminal = true;
                }
                

                else if(a->last->flag == TOKEN_BRACKET_LEFT){
                    
                    a->last->is_startOfExpr = true;
                    a->last->is_expression = false;
                    a->last->is_terminal = true;
                }



                //nie je i, vloz na koniec listu
                else{

                    //ak idu po sebe dva operatory, chyba
                    if((isTokenOperator(a->last->flag)) &&
                        (isTokenOperator(b.flag))){

                        LineErrorException(b, ERROR_SYNTAX, "Two operators in row");
                        return(ERROR_SYNTAX);
                    }

                    a->last->is_startOfExpr = false;
                    a->last->is_terminal = true;
                    a->last->is_expression = true;
                    a->last->prev->is_startOfExpr = true;
                }
                
                

                break;

            case '>':

                //
                //
                //  pravidlo E -> E
                //  TODO: vyhladat ci existuje premenna, vlozit hodnoty, popr. vytvorit novu
                //
                //

                if((a->lastTerminal->is_startOfExpr == true) && 
                    (a->lastTerminal->flag != TOKEN_BRACKET_LEFT)){
                    a->lastTerminal->is_expression = true;
                    a->lastTerminal->is_terminal = false;
                    a->lastTerminal->is_startOfExpr = false;


                    //ak je ID                    
                    if(!(isTokenID(a->lastTerminal->flag)) || !(a->lastTerminal->flag == TOKEN_INTEGER)) {
                        printf("E-> %s \n", a->lastTerminal->name.str);
                    }



                }

                //
                //
                //  pravidlo E -> E x E
                //
                //


                else if ((a->last->flag != TOKEN_BRACKET_LEFT) && (a->last->flag != TOKEN_BRACKET_RIGHT)){


                    PAItem *startExp = a->last;
                        while (startExp->is_startOfExpr == false) {
                            startExp = startExp->prev;
                        }
     
                        a->startExp = startExp;


                    //priradovat mozme iba operandy (ak nie je ID)
                    if(! ((isTokenID(startExp->flag)) || (isTokenID(a->last->flag)) ||
                        (startExp->flag == TOKEN_INTEGER) || (a->last->flag == TOKEN_INTEGER))){
                        LineErrorException(b, ERROR_SYNTAX, "Unexpected expression 2");
                        delete_list(a);
                        return ERROR_SYNTAX;
                    }


                    //pretypuje vysledok, ak pretypovat nejde, error
                    int retType = expeRetype(a->startExp->flag, a->last->flag);
                    if(retType == 0){
                        LineErrorException(b, ERROR_CONVERT, "Can't retype %s to %s\n", getTokenName(a->startExp->flag), getTokenName(a->last->flag));
                        delete_list(a);
                        return ERROR_CONVERT;
                    }


                    a->startExp->flag = retType;
                    a->last->flag = retType;




                    // TODO: podla operatoru (a->lastTerminal->flag) vlozit instrukciu
                    // premenna1 (a->startExp->name.str) = kam vlozit
                    // premenna2 (a->last->name.str) = s cim premennu hore zoperovat
                    //
                    // napr. ADD premenna1 premenna1 premenna2
                    printf("%s = %s %s %s\n", a->startExp->name.str, a->startExp->name.str, getTokenName(a->lastTerminal->flag), a->last->name.str);
                    
                    
                                       

                    free(a->last);
                    free(a->lastTerminal);
                    PAItem * tmp;
                    tmp = startExp;
                    a->last = tmp;

                    a->last->is_terminal = false;
                    a->last->is_expression = true;
                    a->last->is_startOfExpr = false;
                }

                else {


                //
                //
                //  pravidlo E -> ( E )
                //
                //

                  
                        //zarazka (start of expression) bude na predoslom operatore
                        a->startExp = a->startExp->prev->prev;
                        a->startExp->is_startOfExpr = true;


                        //operand si ulozim do tmp, zmazem pravu zatvorku a operand
                        PAItem * tmp = a->lastTerminal->prev;
                        free(a->lastTerminal);
                        free(a->lastTerminal->next);

                        //operand vlozim na koniec listu
                        a->last = tmp;
                        a->last->prev = a->startExp;
                        a->last->next = NULL;                       


                        //pomocny print, redukcia zatvorky
                        printf("%s -> ( %s )\n", a->lastTerminal->prev->name.str, a->lastTerminal->prev->name.str);
                        

                        //ponastavujem flagy a pointry
                        a->lastTerminal = a->last->prev;
                        a->startExp = a->last->prev->prev;

                        a->startExp->is_startOfExpr = true;
                        a->startExp->is_terminal = false;
                        a->startExp->is_expression = true;

                        a->lastTerminal->next = NULL;
                        a->lastTerminal->is_startOfExpr = false;
                        a->lastTerminal->prev->prev->is_expression = true;

                        a->last->is_expression = true;
                        a->last->is_terminal = false;
                        a->last->is_startOfExpr = false;
                        

                }

                break;



            case 'E':

                //koniec, $ == $

                //TODO: vysledok vyrazu je a->startExp
                //vysledna instrukcia: MOVE (vstup) (vysledok)
                printf("\nReturn: MOVE %s@%s LF@%s\n", getFrameName(_return->frame) ,_return->name.str, a->startExp->name.str);
                ErrorException(SUCCESS, "Precedence okay");
                return(SUCCESS);
                break;




            default:
                
                LineErrorException(b, ERROR_SYNTAX, "Unexpected expression");
                return(ERROR_SYNTAX);
                break;

        }
    
    }


delete_list(a);
return SUCCESS;
}
