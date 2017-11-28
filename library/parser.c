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
void parser_init(char * fileNameSource) {
    Token       tok;

    struct Program    _program;
    struct Function   _function;

    scanner_init(fileNameSource);
    program_init(&_program);

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

                // Define Function
                _function = defFunction(&_program, &(tok.ID));

                // Declare Function ID >(<
                tok = scanner_next_token();
                if (tok.flag != TOKEN_BRACKET_RIGHT) {
                    LineErrorException(tok, ERROR_SYNTAX, "( is missing");
                }


                // Declare Function ID ([<STATEMENT> <STATEMENT_LIST>]>)<
                tok = scanner_next_token();
                if (tok.flag == TOKEN_ID) {
                    stateReturn = PARSER_DECLARE_FUNCTION;
                    stateMain   = PARSER_DECLARE_VARIABLE;
                    break;
                }

                /////////////////////////////////////////////
                /**/ LABEL_EndDeclareFunction:
                /////////////////////////////////////////////

                // Declare Function ID (>)<
                if (tok.flag != TOKEN_BRACKET_LEFT) {
                    LineErrorException(tok, ERROR_SYNTAX, ") is missing");
                }

                // Declare Function ID () >AS<
                tok = scanner_next_token();
                if (tok.flag != TOKEN_AS) {
                    LineErrorException(tok, ERROR_SYNTAX, "AS is missing");
                }

                program_dump(_program);
                exit(0);

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
                    case TOKEN_INTEGER: {
                        defFunctionParameter(&_function, tmpID, DATA_TYPE_INT);
                    } break;

                    case TOKEN_DOUBLE: {
                        defFunctionParameter(&_function, tmpID, DATA_TYPE_DOUBLE);
                    } break;

                    case TOKEN_STRING: {
                        defFunctionParameter(&_function, tmpID, DATA_TYPE_STRING);
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



void _dumpFunctions(struct tree_node * node) {
    if (!node) return;
    _dumpFunctions(node->left);


    struct Function * f = node->payload;
    printf("Function(%s) %s()\n", node->key, (f->name).str);

//    Dump("Function(%s) %s()", node->key, f->name->str);
    //_dumpParameters(f->parameters->root);

    _dumpFunctions(node->right);

    return;
}
/*
void _dumpParameters(struct tree_node * node) {
    if (!node) return;

    _dumpParameters(node->left);

    struct DIM * var = node->payload;

    printf("  Parameter (%s) :: %s@%s (%s)\n", node->key, getTokenName(var->dataType), var->name);

    _dumpParameters(node->right);

    return;
}
*/

void dumpFunctions(struct Program p) {
    _dumpFunctions(p.functions->root);
}

void program_dump(struct Program p) {
    printf(":: SCOPE     ::\n");

    printf(":: FUNCTIONS ::\n");
    dumpFunctions(p);
}

/*
*   @function      functions_init
*   @description
*/
void program_init(struct Program * p) {
    p->functions       = new_tree(TREE_PLAIN);
    p->globalVariables = new_tree(TREE_PLAIN);
}


/*
*   @function      functions_init
*   @description
*/
void functionInit(struct Program * p) {
    p->functions       = new_tree(TREE_PLAIN);
    p->globalVariables = new_tree(TREE_PLAIN);
}

/*
*   @function      defFunction
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
struct Function defFunction(struct Program * p, string * name) {

    if (p == NULL || !name->length) {
        ErrorException(ERROR_INTERN, "Parser :: Function Add");
    }

    struct Function f;

    f.priority    = 0;
    f.parameters  = new_tree(TREE_PLAIN);
    f.variables   = new_tree(TREE_PLAIN);
    //f->commands    = ;

    strInit(&(f.name));
    strCopyString(&(f.name), name);

    tree_add(p->functions, name->str, &f);

    return f;
}

/*
*   @function      defFunctionParameter
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
void defFunctionParameter(struct Function * f, string * name, DataType dType) {

    if (f == NULL || !name->length) {
        ErrorException(ERROR_INTERN, "Parser :: Add Parameter");
    }

    struct DIM var = defParameter(name, dType);

    tree_add(f->parameters, name->str , &var);
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

struct DIM defParameter(string * name, DataType dType) {

    string value;
    strInit(&value);

    struct DIM parameter = createVariable(name, &value, dType, FRAME_PARAMETERS);

    return parameter;
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

