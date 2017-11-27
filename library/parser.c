///////////////////////////////////////////////////////////////////////////////////
//
//	@Project 			IFJ 2017
//
//  @Authors
//  Kristýna Jandová  	xjando04
//  Vilém Faigel		xfaige00
//  Nikola Timková		xtimko01
//	Bc. Václav Doležal	xdolez76
//
//	@File				tokens.c
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////
//
//  PARSER
//

#include "parser.h"

enum ParserStats {
    PARSER_START,
    PARSER_DECLARE_FUNCTION,
    PARSER_DECLARE_VARIABLE,
    PARSER_END
};

/*
*   @function      parserInit
*   @param         char * fileNameSource
*   @param         string       name
*   @description
*/
void parserInit(char * fileNameSource) {
    Token       tok;

    struct Program    _program;
    struct Function   _function;
    scanner_init(fileNameSource);

    programInit(&_program);

    int stateMain   = PARSER_START,
        stateReturn = PARSER_START;

    while(stateMain != PARSER_END) {
        switch(stateMain) {

            ////////////////////////////////////
            //
            case PARSER_START: {
                tok = scanner_next_token();
                switch(tok.flag) {
                    case TOKEN_DECLARE:
                        stateMain = PARSER_DECLARE_FUNCTION;
                    break;
                }
            } break;

            ///////////////////////////////////////////////////////////////////////
            // Declare Function ID (ID As DT[, ID As DT] ..) As DT
            //
            case PARSER_DECLARE_FUNCTION: {

                // Declare >Function<
                tok = scanner_next_token();
                if (tok.flag != TOKEN_FUNCTION) {
                    LineErrorException(tok, ERROR_SYNTAX, "Function is missing");
                }

                // Declare Function >ID<
                tok = scanner_next_token();
                if (tok.flag != TOKEN_ID) {
                    LineErrorException(tok, ERROR_SYNTAX, "ID of function is missing");
                }

                // Create Function
                _function = functionsAdd(&_program, &(tok.ID));

                // Declare Function ID >(<
                tok = scanner_next_token();
                if (tok.flag == TOKEN_BRACKET_LEFT) {

                    // Declare Function ID ([<STATEMENT> <STATEMENT_LIST>]>)<
                    tok = scanner_next_token();

                    switch(tok.flag) {
                        case TOKEN_ID: {
                            stateReturn = PARSER_DECLARE_FUNCTION;
                        } break;
                    }
                }



                tok = scanner_next_token();
                if (tok.flag == TOKEN_BRACKET_LEFT) {

                    // Declare Function ID ([<STATEMENT> <STATEMENT_LIST>]>)<

                    tok = scanner_next_token();
                    if (tok.flag == TOKEN_ID)
                        stateReturn = PARSER_DECLARE_FUNCTION;

                    /////////////////////////////////////////////
                    /**/ LABEL_EndDeclareFunction:
                    /////////////////////////////////////////////

                    tok = scanner_next_token();
                    if (tok.flag != TOKEN_BRACKET_RIGHT) {
                        LineErrorException(tok, ERROR_SYNTAX, ") is missing");
                    }
                }


            } break;

            ///////////////////////////////////////////////////////////////////////
            // Declare Function ID (ID As DT[, ID As DT] ..) As DT
            //
            case PARSER_DECLARE_VARIABLE: {

                /////////////////////////////////////////////
                /**/ LABEL_DataType:
                /////////////////////////////////////////////

                // >ID< As DT
                if (tok.flag != TOKEN_ID) {
                    LineErrorException(tok, ERROR_SYNTAX, "ID is missing");
                }

                string * tmpID = &(tok.ID);

                // ID >As< DT
                tok = scanner_next_token();
                if (tok.flag != TOKEN_AS) {
                    LineErrorException(tok, ERROR_SYNTAX, "AS is missing");
                }

                // ID As >DT<
                tok = scanner_next_token();
                switch (tok.flag) {
                    case TOKEN_INTEGER:
                    case TOKEN_DOUBLE:
                    case TOKEN_STRING: {
                        functionDefParameter(&_function, tmpID, tok.flag);
                    } break;

                    default: {
                        LineErrorException(tok, ERROR_SYNTAX, "Data Type is missing");
                    }
                }

                tok = scanner_next_token();

                // ID As DT>[, ID As DT ..]<
                if (tok.flag == TOKEN_COMMA)                goto LABEL_DataType;
                if (stateReturn == PARSER_DECLARE_FUNCTION) goto LABEL_EndDeclareFunction;

            } break;

        }
    }
}
///////////////////////////////////////////////////////////////////////////////////
//
//  FUNCTIONS
//


/*
*   @function      functionsInit
*   @description
*/
void programInit(struct Program * p) {
    p->functions       = new_tree(TREE_PLAIN);
    p->globalVariables = new_tree(TREE_PLAIN);
}


/*
*   @function      functionAdd
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
struct Function functionsAdd(struct Program * p, string * name) {

    if (p == NULL || !name->length) {
        ErrorException(ERROR_INTERN, "Parser :: Function Add");
    }

    struct Function f;



    strInit(&(f.name));
    strCopyString(&(f.name), name);

    tree_add(p->functions, name->str, &f);

    return f;
}

/*
*   @function      functionAdd
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
void functionDefParameter(struct Function * f, string * name, DataType dType) {

    if (f == NULL || !name->length) {
        ErrorException(ERROR_INTERN, "Parser :: Add Parameter");
    }

    struct DIM var;
    string     value;

    strInit(&value);

    var = createVariable(name, &value, dType, FRAME_LOCAL);

    tree_add(f->parameters, name->str, &var);

}


/*
*   @function      functionAdd
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/

struct DIM createVariable(string * name, string * value, DataType dType, DIMFrame frame) {

    if (!name->length) {
        ErrorException(ERROR_RUNTIME, "Create Variable :: NAME IS NULL");
    }

    struct DIM variable;

    strInit(&(variable.name));
    strCopyString(&(variable.name), name);

    variable.dataType = dType;
    variable.frame    = frame;
    if (value->length) {
        switch (dType) {
            case DATA_TYPE_INT: {
                variable.valueInteger = atoi(value->str);
            } break;
            case DATA_TYPE_DOUBLE: {
                char *ptr;
                variable.valueDouble  = strtod(value->str, &ptr);
            } break;
            case DATA_TYPE_STRING: {
                strInit(&(variable.valueString));
                strCopyString(&(variable.valueString), value);
            } break;
        }
    }

    return variable;
}







/*
*   @function      functionAdd
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
//void parser_set_setting(parserSetting setting);



/*
*   @function      functionAdd
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
//void parser_run(char * fileNameDestiny) {}


/*
*   @function      functionAdd
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
//void addFunctionParam(Function * fce, string name, short int dateType) {}


/*
*   @function      functionAdd
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
//void dumpFunctionParams(Function * fce) {}

