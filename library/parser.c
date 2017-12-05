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

    //
    //
    // <PARAM>
    PARSER_PARAMS,

    //
    //
    // DECLARE FUNCTION (ID) ( <PARAM> ) AS <TYPE> EOL
    PARSER_DECLARE_FUNCTION_START,
    PARSER_DECLARE_FUNCTION_PARAMETERS,
    PARSER_DECLARE_FUNCTION_END,

    //
    //
    // FUNCTION (ID) ( <PARAM> ) AS <TYPE> EOL
    PARSER_DEFINE_FUNCTION_START,
    PARSER_DEFINE_FUNCTION_PARAMETERS,
    PARSER_DEFINE_FUNCTION_RETURN,
    PARSER_DEFINE_FUNCTION_STATMENTS,
    PARSER_DEFINE_FUNCTION_END,

    //
    // IF <EXPRESSION> THEN EOL <STATEMENT_LIST> <ELSEIF> <ELSE> END IF
    PARSER_STATMENT_IF,

    //
    // DO WHILE <EXPRESSION> EOL <STATEMENT_LIST> <LOOP>
    PARSER_STATMENT_WHILE,

    //
    // DIM (ID) AS <TYPE> EOL
    PARSER_STATMENT_DIM,

    //
    // DIM (ID) AS <TYPE> <EXPRESSION> EOL
    PARSER_STATMENT_DIM_ASSIGNMENT,

    //
    // (ID) = <EXPRESSION> EOL
    PARSER_STATMENT_ID_ASSIGNMENT,

    //
    // (ID) = FUNCTION_ID ( <PARAM> ) EOL
    PARSER_STATMENT_ID_ASSIGNMENT_FUNCTION,

    //
    // INPUT (ID) EOL
    PARSER_STATMENT_INPUT,

    //
    // PRINT <EXPRESSION> EOL
    PARSER_STATMENT_PRINT,

    //
    // FUNCTION (ID) ( <PARAM> ) AS <TYPE> EOL
    PARSER_EOL,

    //
    // FUNCTION (ID) ( <PARAM> ) AS <TYPE> EOL
    PARSER_END
};


struct Program      *__parser_program;
Token               tok;

/*
*   @function      parser_init
*   @param         char * fileNameSource
*   @description
*/
void parser_init(char * fileNameSource) {

    scanner_init(fileNameSource);
    program_init(&__parser_program);

}


#define FUNCTION_DECLARE 0
#define FUNCTION_DEFINE  1

/*
*   @function      parser_run
*   @description
*/
void parser_run() {

    struct Function *_function;

    int stateMain   = PARSER_START,
        stateReturn = PARSER_START;

    int dType,
        counterDefineParams = 0,
        functionStats       = FUNCTION_DECLARE;

    while(stateMain != PARSER_END) {
        switch(stateMain) {

            ////////////////////////////////////
            //
            case PARSER_START: {
                tok = scanner_next_token();
                switch(tok.flag) {
                    case TOKEN_DECLARE:
                        stateMain = PARSER_DECLARE_FUNCTION_START;
                    break;
                    case TOKEN_FUNCTION:
                        stateMain = PARSER_DEFINE_FUNCTION_START;
                    break;
                    case TOKEN_IF:
                        stateMain = PARSER_STATMENT_IF;
                    break;
                    case TOKEN_DO:
                        stateMain = PARSER_STATMENT_WHILE;
                    break;
                    case TOKEN_END_OF_LINE:
                        stateMain = PARSER_START;
                    break;
                    case TOKEN_END_OF_FILE:
                        stateMain = PARSER_END;
                    break;
                }
            } break;

            ///////////////////////////////////////////////////////////////////////
            // Declare Function ID (ID As DT[, ID As DT] ..) As DT
            //
            case PARSER_DECLARE_FUNCTION_START: {

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

                ////////////////////////////////////
                //
                _function = functionDeclare(__parser_program, &(tok.ID));
                //

                // Declare Function ID >(<
                tok = scanner_next_token();
                if (tok.flag != TOKEN_BRACKET_LEFT) {
                    LineErrorException(tok, ERROR_SYNTAX, "( is missing");
                }

                // Declare Function ID ( [<PARAM>] )
                tok = scanner_next_token();
                if (tok.flag == TOKEN_ID) {
                    stateMain           = PARSER_DECLARE_FUNCTION_PARAMETERS;
                } else {
                    stateMain           = PARSER_DECLARE_FUNCTION_END;
                }

            } break;

            case PARSER_DECLARE_FUNCTION_PARAMETERS: {
                stateMain   = PARSER_PARAMS;
                stateReturn = PARSER_DECLARE_FUNCTION_END;

            } break;

            case PARSER_DECLARE_FUNCTION_END: {

                tok = scanner_next_token();

                struct DIM * _return;

                // Declare Function ID () AS DT
                if (tok.flag == TOKEN_AS) {

                    tok = scanner_next_token();
                    if ((dType = getDataTypeFromToken(tok.flag)) != -1 ) {

                        _return = DIMInitReturn(getDataTypeFromToken(tok.flag));

                    } else {
                        LineErrorException(tok, ERROR_SYNTAX, "Data Type is missing");
                    }
                }

                // Declare Function ID () EOL
                else if (tok.flag == TOKEN_END_OF_LINE) {
                    _return = DIMInitReturn(DATA_TYPE_VOID);

                } else {
                    LineErrorException(tok, ERROR_SYNTAX, "AS is missing");
                }

                _function->_return = _return;

                Dump("> DECLARE Function %s() return@%s\n", (_function->name).str, getDataTypeName(_return->dataType));

                stateMain   = PARSER_START;
            } break;

            ///////////////////////////////////////////////////////////////////////
            // Function ID (ID As DT[, ID As DT] ..) As DT
            //
            case PARSER_DEFINE_FUNCTION_START: {

                // Declare Function >ID<
                tok = scanner_next_token();
                if (tok.flag != TOKEN_ID) {
                    LineErrorException(tok, ERROR_SYNTAX, "ID of function is missing");
                }

                /////////////////////////////////////
                //
                _function = functionDefine(__parser_program, &(tok.ID));
                //

                // Declare Function ID >(<
                tok = scanner_next_token();
                if (tok.flag != TOKEN_BRACKET_LEFT) {
                    LineErrorException(tok, ERROR_SYNTAX, "( is missing");
                }

                // Declare Function ID ( [<PARAM>] )
                tok = scanner_next_token();
                if (tok.flag == TOKEN_ID) {
                    stateMain   = PARSER_DEFINE_FUNCTION_PARAMETERS;
                } else {
                    stateMain   = PARSER_DEFINE_FUNCTION_STATMENTS;
                }

            } break;

            case PARSER_DEFINE_FUNCTION_PARAMETERS: {
                stateMain   = PARSER_PARAMS;
                stateReturn = PARSER_DEFINE_FUNCTION_RETURN;
            } break;

            case PARSER_DEFINE_FUNCTION_RETURN: {

                tok = scanner_next_token();

                struct DIM * _return;

                // Declare Function ID () AS DT
                if (tok.flag == TOKEN_AS) {

                    tok = scanner_next_token();
                    if ((dType = getDataTypeFromToken(tok.flag)) != -1 ) {

                        _return = DIMInitReturn(getDataTypeFromToken(tok.flag));

                    } else {
                        LineErrorException(tok, ERROR_SYNTAX, "Data Type is missing");
                    }

                // Declare Function ID () >EOL
                } else if (tok.flag == TOKEN_END_OF_LINE) {
                    _return = DIMInitReturn(DATA_TYPE_VOID);
                } else {
                    LineErrorException(tok, ERROR_SYNTAX, "AS is missing");
                }

                if (_function->_return->dataType != _return->dataType) {
                    LineErrorException(tok, ERROR_LEXICAL, "Return in function %s() an '%s' type was specified, the '%s' data type is expected",
                                   (_function->name).str, getDataTypeName(_function->_return->dataType), getDataTypeName(_return->dataType)
                    );
                }

                _function->_return = _return;

                Dump("> DEFINE Function %s() return@%s\n", (_function->name).str, getDataTypeName(_return->dataType));

                stateMain = PARSER_DEFINE_FUNCTION_STATMENTS;

            } break;

            case PARSER_DEFINE_FUNCTION_STATMENTS: {


                while (tok.flag != TOKEN_END && tok.flag != TOKEN_END_OF_FILE && tok.flag != TOKEN_IF) {
                    tok = scanner_next_token();
                }


                if (tok.flag == TOKEN_IF) {
                    stateMain = PARSER_STATMENT_IF;
                    break;
                }


                tok = scanner_next_token();

                if (tok.flag == TOKEN_FUNCTION) {
                    stateMain = PARSER_DEFINE_FUNCTION_END;
                } else {
                    stateMain = PARSER_DEFINE_FUNCTION_STATMENTS;
                }

            } break;

            case PARSER_DEFINE_FUNCTION_END: {

                if (tok.flag != TOKEN_FUNCTION) {
                    LineErrorException(tok, ERROR_SYNTAX, "FUNCTION is missing");
                }

                Dump("> DEFINE Function %s() COMPLETE\n", (_function->name).str);

                stateMain   = PARSER_START;
            } break;

            ///////////////////////////////////////////////////////////////////////
            // IF <extension> THEN EOL <statments> ELSE <statmens> END IF
            //
            case PARSER_STATMENT_IF: {

                // IF <extension>

                // Call getExpression
                struct DIM * _return        = malloc(sizeof(struct DIM));
                struct tree * commandsBlock = new_tree(TREE_PLAIN);

                _return->dataType = DATA_TYPE_INT;

                getExpression(commandsBlock, _return);

                /////////////////////////////////
                // IF výraz = true

                // Print label instruction
                /////////////////////////////////

                tok = scanner_next_token();
		        if (tok.flag != TOKEN_THEN) {
		            LineErrorException(tok, ERROR_SYNTAX, "THEN is missing");
		        }


		        tok = scanner_next_token();
		        if (tok.flag != TOKEN_END_OF_LINE) {
		            LineErrorException(tok, ERROR_SYNTAX, "must be end of line");
		        }

		        /////////////////////////////////
                // Print label instruction
                /////////////////////////////////

                while(tok.flag != TOKEN_ELSE){
                    tok = scanner_next_token();
                    if (tok.flag == TOKEN_END_OF_FILE) {
                        LineErrorException(tok, ERROR_SYNTAX, "reached end, ELSE is missing");
                    }
                }

                //IF výraz = false skip till ELSE

                tok = scanner_next_token();
                if (tok.flag != TOKEN_END_OF_LINE) {
                    LineErrorException(tok, ERROR_SYNTAX, "must be end of line");
                }

                //tu se vyhodnoti dalsi prikazy

                //ending of if statement (END IF)
                tok = scanner_next_token();
                if (tok.flag != TOKEN_END) {
                    LineErrorException(tok, ERROR_SYNTAX, "missing END IF statement");
                }

                tok = scanner_next_token();
                if (tok.flag != TOKEN_IF) {
                    LineErrorException(tok, ERROR_SYNTAX, "missing END IF statement");
                }

                stateMain = PARSER_DEFINE_FUNCTION_STATMENTS;
            }; break;

            ///////////////////////////////////////////////////////////////////////
            // DO WHILE výraz EOL
            // příkazy
            // LOOP
            case PARSER_STATMENT_WHILE: {
                tok = scanner_next_token();
                if (tok.flag != TOKEN_WHILE) {
                    LineErrorException(tok, ERROR_SYNTAX, "missing WHILE statement");
                }

                //tu se vola PA pro vyhodnocení výrazu
                tok = scanner_next_token();
                if (tok.flag != TOKEN_END_OF_LINE) {
                    LineErrorException(tok, ERROR_SYNTAX, "must be nd of line");
                }

                while(tok.flag != TOKEN_LOOP) {

                    tok = scanner_next_token();
                //tu jede vyhodnocování věcí v cyklu, +kontroluji jestli není ukončovací podmínka (pro BASIC)
                }
            }; break;

            case PARSER_PARAMS : {

                // >ID< As DT
                if (tok.flag != TOKEN_ID) {
                    LineErrorException(tok, ERROR_SYNTAX, "ID is missing");
                }

                string tmpID = tok.ID;

                // ID >As< DT
                tok = scanner_next_token();
                if (tok.flag != TOKEN_AS) {
                    LineErrorException(tok, ERROR_SYNTAX, "AS is missing");
                }

                // ID As >DT<
                tok = scanner_next_token();
                if ((dType = getDataTypeFromToken(tok.flag)) != -1 ) {

                    /////////////////////////////////////
                    //
                    switch(functionStats) {
                        case FUNCTION_DECLARE: functionDeclareParameters(_function, &tmpID, dType); break;
                        case FUNCTION_DEFINE:  functionDefineParameters(_function, &tmpID, dType, counterDefineParams); break;
                        default: ErrorException(ERROR_INTERN, "Unknown function stats");
                    }
                    //
                    /////////////////////////////////////

                } else {
                    LineErrorException(tok, ERROR_SYNTAX, "Data Type is missing");
                }

                // ID As DT>[, ID As DT ..]<
                tok = scanner_next_token();

                switch (tok.flag) {

                    case TOKEN_COMMA: {
                        tok       = scanner_next_token();
                        counterDefineParams++;
                        stateMain = PARSER_PARAMS;
                    } break;

                    case TOKEN_BRACKET_RIGHT: {
                        counterDefineParams=0;
                        stateMain = stateReturn; break;
                    }

                    default: LineErrorException(tok, ERROR_SYNTAX, ") is missing");
                }
            } break;
        }
    }

    program_dump(__parser_program);
    exit(0);
}


///////////////////////////////////////////////////////////////////////////////////
//
//  FUNCTIONS
//


/*
*   @function      functions_init
*   @description
*/
void program_init(struct Program ** p) {

    struct Program * _p = malloc(sizeof(struct Program));
    _p->functions       = new_tree(TREE_PLAIN);
    _p->globalVariables = new_tree(TREE_PLAIN);
    *p = _p;
}


/*
*   @function      functionDeclare
*   @param         struct Program * p
*   @param         string *         name
*   @description
*/
struct Function * functionDeclare(struct Program * p, string * name) {

    if (p == NULL) {
        ErrorException(ERROR_INTERN, "Parser :: Function Add :: Program is NULL");
    }

    if (!name->length) {
        ErrorException(ERROR_INTERN, "Parser :: Function Add :: ID is NULL");
    }

    Dump("> DECLARE Function %s()\n", name->str);

    struct Function * f = malloc( sizeof(struct Function));

    f->parameters       = malloc(sizeof(list));

    list_new(f->parameters, sizeof(struct DIM));

    f->priority   = 0;
    f->variables  = new_tree(TREE_PLAIN);

    strInit(&(f->name));
    strCopyString(&(f->name), name);

    tree_add(p->functions, name->str, f);

    return f;
}


/*
*   @function      functionDeclareParameters
*   @param         struct Function * f
*   @param         string *          name
*   @param         DataType          dType
*   @description
*/
void functionDeclareParameters(struct Function * f, string * name, DataType dType) {

    if (f == NULL || !name->length) {
        ErrorException(ERROR_INTERN, "Parser :: Add Parameter");
    }

    struct DIM * var = declareParameter(name, dType);

    Dump("> DECLARE Function %s() Param :: %s@%s\n", (f->name).str, (var->name).str, getDataTypeName(dType));

    list_append(f->parameters, var);
}


/*
*   @function      functionIsExists
*   @param         struct Program * p
*   @param         string *          name
*   @description
*/
struct Function * functionIsExists(struct Program * p, string * name) {

    struct Function * f;

    if (tree_get(p->functions, name->str, (void *) &f)) {
        Dump("> FUNCTION %s() IS DECLARED\n", name->str);
    } else {
        ErrorException(ERROR_SYNTAX, "FUNCTION %s() IS NOT DECLARED", name->str);
    }

    return f;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  DEFINE FUNCTION
//


/*
*   @function      functionDefine
*   @param         struct Program * p
*   @param         string *         name
*   @description
*/
struct Function * functionDefine(struct Program * p, string * name) {

    if (p == NULL || !name->length) {
        ErrorException(ERROR_INTERN, "Parser :: Function Define");
    }

    Dump("> DEFINE Function %s()", name->str);

    struct Function * f = functionIsExists(p, name);

    return f;
}


/*
*   @function      functionDefineParameters
*   @param         struct Function * f
*   @param         string *          name
*   @param         DataType          dType
*   @description
*/
void functionDefineParameters(struct Function * f, string * name, DataType dType, int index) {

    if (f == NULL || !name->length) {
        ErrorException(ERROR_INTERN, "Parser :: Function Define Parameters");
    }

    if (index >= list_size(f->parameters)) {
        ErrorException(ERROR_SYNTAX, "Multiple parameters defined");
    }

    struct DIM * var = (struct DIM*) list_index(f->parameters, index);

    if ((int) var->dataType != (int) dType) {
        ErrorException(ERROR_LEXICAL, "An '%s' type was specified, the '%s' data type is expected", getDataTypeName(var->dataType), getDataTypeName(dType));
    }

    strCopyString(&var->name, name);

    Dump("> DEFINE Function %s() Param_%d :: %s@%s\n", (f->name).str, index, name->str, getDataTypeName(dType));
}


/*
*   @function      declareParameter
*   @param         string * name
*   @param         string DataType dType
*   @description
*/
struct DIM * declareParameter(string * name, DataType dType) {

    string value;
    strInit(&value);

    struct DIM * parameter = createVariable(name, &value, dType, FRAME_PARAMETERS);

    return parameter;
}

///////////////////////////////////////////////////////////////////////////////////
//
//  EXPRESION
//

void getExpression(struct tree * commands, struct DIM * _return) {

    Dump("Expression");

    Token tok = scanner_next_token();
    short int bracket_count = 0,
              is_operator   = -1;

    while(tok.flag != TOKEN_END_OF_FILE && tok.flag != TOKEN_END_OF_LINE && tok.flag != TOKEN_THEN) {
        if (tok.flag == TOKEN_BRACKET_LEFT) {
            bracket_count++;

        } else if (tok.flag == TOKEN_BRACKET_RIGHT) {
            bracket_count--;

        } else {
            if (is_operator == -1) {
                is_operator = isTokenOperator(tok.flag);
            } else {
                if (is_operator == isTokenOperator(tok.flag)) {
                    LineErrorException(tok, ERROR_LEXICAL, "Exception LL");
                } else {
                    is_operator = isTokenOperator(tok.flag);
                }
            }
        }

        tok = scanner_next_token();
    }


    if (bracket_count) {
        LineErrorException(tok, ERROR_LEXICAL, "In Exception : Bracket");
    }

    _return->valueInteger = 3;
    _return->valueDouble  = 3.14;
    _return->valueString  = strChars("3.14");

    unused(commands);
}



///////////////////////////////////////////////////////////////////////////////////
//
//  DUMP PROGRAM
//


void dumpFunctions(struct Program * p) {

    struct tree      * t = p->functions;
    struct tree_iter it;
    struct Function  * f;

    tree_iter_init(&it, t);
    while (tree_iter_next(&it)) {
        f = it.item.payload;

        printf("Function %s()\n", (f->name).str);

        dumpParameters(f);

        printf("Return @%s\n\n", getDataTypeName(f->_return->dataType));
    }

    return;
}


void dumpParameters(struct Function * f) {

    list        * params = f->parameters;
    struct DIM  * var;

    int paramCount = list_size(params);

    printf("Parameter Count(%d)\n", paramCount);
    for(int i = 0; i < paramCount; i++) {
        var = list_index(params, i);
        printf("Parameter :: %s@%s\n", (var->name).str, getDataTypeName(var->dataType));
    }
}


void program_dump(struct Program * p) {
    printf("\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf(":: DUMP PROGRAM \n");
    printf("::\n:: SCOPE\n");

    printf("::\n:: FUNCTIONS::\n");
    dumpFunctions(p);
}

//void dumpFunctionParams(Function * fce) {}

