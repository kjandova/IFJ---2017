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
        case DATA_TYPE_DOUBLE:
        case DATA_TYPE_STRING:
        case DATA_TYPE_INT:
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



//im going to hell for this
int returnCommands(struct DIM * item1, struct DIM * item2, int flag){


    int instruct;

    switch(flag){

        case TOKEN_ADD:
            if(item1->dataType == DATA_TYPE_STRING){
                instruct = I_CONCAT;
                generateInstruction(__parser->function_commands, instruct, item1, item1, item2);
            }
            if((item1->dataType == DATA_TYPE_DOUBLE) || (item1->dataType == DATA_TYPE_INT)){
                instruct = I_ADD;
                generateInstruction(__parser->function_commands, instruct, item1, item1, item2);
            }
        break;

        case TOKEN_SUB:
            instruct = I_SUB;
            generateInstruction(__parser->function_commands, instruct, item1, item1, item2);
        break;

        case TOKEN_MUL:
            instruct = I_MUL;
            generateInstruction(__parser->function_commands, instruct, item1, item1, item2);
        break;

        case TOKEN_DIV:

            if(item1->dataType != DATA_TYPE_DOUBLE){
                instruct = I_INT2FLOAT;
                generateInstruction(__parser->function_commands, instruct, item1, item1, item2);
            }
            instruct = I_DIV;
            generateInstruction(__parser->function_commands, instruct, item1, item1, item2);
        break;

        case TOKEN_BACKSLASH:
            if(item1->dataType == DATA_TYPE_INT){
                instruct = I_DIV;
                generateInstruction(__parser->function_commands, instruct, item1, item1, item2);
            }
            else{
                ErrorException(ERROR_SYNTAX, "Backslash devide operands not INT");
                return(ERROR_SYNTAX);
            }
        break;


        case TOKEN_LESS:
            instruct = I_LT;
            generateInstruction(__parser->function_commands, instruct, item1, item1, item2);
        break;


        case TOKEN_MORE:
            instruct = I_GT;
            generateInstruction(__parser->function_commands, instruct, item1, item1, item2);
        break;


        case TOKEN_EQUALS:
            instruct = I_EQ;
            generateInstruction(__parser->function_commands, instruct, item1, item1, item2);
        break;


        case TOKEN_MORE_OR_EQUAL:
            instruct = I_EQ;
            generateInstruction(__parser->function_commands, instruct, item1, item1, item2);
            instruct = I_GT;
            generateInstruction(__parser->function_commands, instruct, item1, item1, item2);
            instruct = I_OR;
            generateInstruction(__parser->function_commands, instruct, item1, item1, item2);
        break;

        case TOKEN_LESS_OR_EQUAL:
            instruct = I_EQ;
            generateInstruction(__parser->function_commands, instruct, item1, item1, item2);
            instruct = I_LT;
            generateInstruction(__parser->function_commands, instruct, item1, item1, item2);
            instruct = I_OR;
            generateInstruction(__parser->function_commands, instruct, item1, item1, item2);
        break;

        case TOKEN_NON_EQUAL:
            instruct = I_NOT;
            generateInstruction(__parser->function_commands, instruct, item1, item2, NULL);
        break;

    }

return SUCCESS;
}



/*
*   @function      prec_anal
*   @param         struct Statment * s
*   @param         DIM * _return
*/
            
int getExpression(struct DIM * _return){

    //
    //
    // Precedencna analyza
    //
    //

    //scanner_init("./tests/PA/Test_1.bas");
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

                if((run == 1) && ((b.flag == TOKEN_END_OF_LINE) || (b.flag == TOKEN_THEN))){
                    Dump("E-> %s\n", a->last->name.str);

                    struct DIM * var = searchVariable(__parser_program, __parser_function, &a->last->name);
                    if(var){
                        a->last->prem = var;
                    }
                    else{

                        LineErrorException(b, ERROR_UNINIT, "Unitialized variable used in expression");
                    }

                    generateInstruction(__parser->function_commands, I_MOVE, _return, a->last->prem, NULL);
                    delete_list(a);
                    return SUCCESS;
                }


                if(isTokenID(a->last->flag)){
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
                        //return(ERROR_SYNTAX);
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
                //  vyhladat ci existuje premenna, vlozit hodnoty, popr. vytvorit novu
                //
                

                if((a->lastTerminal->is_startOfExpr == true) && 
                    (a->lastTerminal->flag != TOKEN_BRACKET_LEFT)){
                    a->lastTerminal->is_expression = true;
                    a->lastTerminal->is_terminal = false;
                    a->lastTerminal->is_startOfExpr = false;


                    //ak je ID                    
                    if(isTokenID(a->lastTerminal->flag)) {


                        //ak je to samotny int, double, alebo string
                        if((a->lastTerminal->flag == DATA_TYPE_INT) || (a->lastTerminal->flag == DATA_TYPE_DOUBLE) ||
                           (a->lastTerminal->flag == DATA_TYPE_STRING)){

                            //int iterator;
                            string name;
                            name.str = "pomocna";
                            string value;
                            value.str = "nieco";

                            createVariable(&name, &value, a->lastTerminal->flag, _return->frame);
                            Dump("Creating new variable for %s", a->lastTerminal->name.str);
                        }

                        //ak to je premenna, vyhlada, ci existuje
                        struct DIM * var = searchVariable(__parser_program, __parser_function, &a->lastTerminal->name);
                        

                        //premenna existuje, narvem ju do item
                        if(var){
                            a->lastTerminal->prem = var;
                            Dump("variable OK; already exists in symtable");
                            }

                        //premmenna neexistuje, error    
                        else{
                            LineErrorException(b, ERROR_UNINIT, "Unitialized variable used in expression");
                            return ERROR_UNINIT;
                        }
                    
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


                    //priradovat mozme iba operandy
                    if(!((isTokenID(startExp->flag)) || (isTokenID(a->last->flag)))) {
                        LineErrorException(b, ERROR_SYNTAX, "Unexpected expression operands");
                        delete_list(a);
                        return ERROR_SYNTAX;
                    }


                    //ak je jeden z operandov string 
                    //mozme pouzit + (ktore sa neskor musi vyhodnotit ako concat), <> alebo =

                    if((a->startExp->flag == DATA_TYPE_STRING) || (a->last->flag == DATA_TYPE_STRING)){
                        if (!((a->lastTerminal->flag == TOKEN_ADD) || (a->lastTerminal->flag == TOKEN_NON_EQUAL) ||
                            (a->lastTerminal->flag == TOKEN_EQUALS))){
                            LineErrorException(b, ERROR_SYNTAX, "Illegal operation");
                            delete_list(a);
                            //return ERROR_SYNTAX;
                        }
                    }


                    //pretypuje vysledok, ak pretypovat nejde, error
                    /*int retType = expeRetype(a->startExp->flag, a->last->flag);
                    if(retType == 0){
                        LineErrorException(b, ERROR_CONVERT, "Can't retype %s to %s\n", getTokenName(a->startExp->flag), getTokenName(a->last->flag));
                        delete_list(a);
                        return ERROR_CONVERT;
                    }


                    a->startExp->flag = retType;
                    a->last->flag = retType;

                    */


                    // podla operatoru (a->lastTerminal->flag) vlozit instrukciu
                    // premenna1 (a->startExp->name.str) = kam vlozit
                    // premenna2 (a->last->name.str) = s cim premennu hore zoperovat
                    //
                    // napr. ADD premenna1 premenna1 premenna2

                    int p;
                    if((p = (returnCommands(a->startExp->prem, a->last->prem, a->lastTerminal->flag)) == 0)){
                        Dump("succesfully returned commands");
                    }
                    Dump("%s = %s %s %s\n", a->startExp->name.str, a->startExp->name.str, getTokenName(a->lastTerminal->flag), a->last->name.str);
                    
                                                       

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
                        Dump("%s -> ( %s )\n", a->lastTerminal->prev->name.str, a->lastTerminal->prev->name.str);
                        
                        //printList(a);
                        //ponastavujem flagy a pointry
                        a->lastTerminal = a->last->prev;


                        //ak nie je posledny terminal $
                        if(a->lastTerminal->flag != TOKEN_END_OF_LINE){
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


                    }

                break;



            case 'E':

                //vysledna instrukcia: MOVE (vstup) (vysledok)
                generateInstruction(__parser->function_commands, I_MOVE, _return, a->startExp->prem, NULL);
                //Dump("\nReturn: MOVE %s@%s LF@%s\n", getFrameName(_return->frame) ,_return->name.str, a->startExp->name.str);
                ErrorException(SUCCESS, "Precedence okay");
                return(SUCCESS);
                break;




            default:
               // Dump("[%d][%d]\n", i, j);
                LineErrorException(b, ERROR_SYNTAX, "Unexpected expression");
                return(ERROR_SYNTAX);
                break;

        }
    }


delete_list(a);
return SUCCESS;
}
