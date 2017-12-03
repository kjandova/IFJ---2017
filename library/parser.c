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
    // DECLARE FUNCTION (ID) ( <PARAM> ) AS <TYPE> EOL
    PARSER_DECLARE_FUNCTION_START,
    PARSER_DECLARE_FUNCTION_PARAMETERS,
    PARSER_DECLARE_FUNCTION_END,

    //
    //
    // FUNCTION (ID) ( <PARAM> ) AS <TYPE> EOL
    PARSER_DEFINE_FUNCTION_START,
    PARSER_DEFINE_FUNCTION_PARAMETERS,
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


/*
*   @function      parser_run
*   @description
*/
void parser_run() {

    struct Function *_function;

    int stateMain   = PARSER_START;

    int dType;

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

                _function = declareFunction(__parser_program, &(tok.ID));

                // Declare Function ID >(<
                tok = scanner_next_token();
                if (tok.flag != TOKEN_BRACKET_LEFT) {
                    LineErrorException(tok, ERROR_SYNTAX, "( is missing");
                }

                // Declare Function ID ( [<PARAM>] )
                tok = scanner_next_token();
                if (tok.flag == TOKEN_ID) {
                    stateMain   = PARSER_DECLARE_FUNCTION_PARAMETERS;
                } else {
                    stateMain   = PARSER_DECLARE_FUNCTION_END;
                }

            } break;

            case PARSER_DECLARE_FUNCTION_PARAMETERS: {

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
                    declareFunctionParameter(_function, &tmpID, dType);
                } else {
                    LineErrorException(tok, ERROR_SYNTAX, "Data Type is missing");
                }

                // ID As DT>[, ID As DT ..]<
                tok = scanner_next_token();

                switch (tok.flag) {
                    case TOKEN_COMMA: {
                        tok       = scanner_next_token();
                        stateMain = PARSER_DECLARE_FUNCTION_PARAMETERS;
                    } break;
                    case TOKEN_BRACKET_RIGHT:  stateMain = PARSER_DECLARE_FUNCTION_END; break;
                    default: LineErrorException(tok, ERROR_SYNTAX, ") is missing");
                }
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

                stateMain   = PARSER_START;
            } break;

            ///////////////////////////////////////////////////////////////////////
            // IF <extension> THEN EOL <statments> ELSE <statmens> END IF

            case PARSER_STATMENT_IF:

                // IF <extension>
                //struct DIM * _return = malloc(sizeof(struct DIM));

                //_return->dataType = DATA_TYPE_INT;

                //getExpression(_return);

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
                break;


            ///////////////////////////////////////////////////////////////////////
            // DO WHILE výraz EOL
	    // příkazy
            // LOOP
	    case PARSER_STATMENT_WHILE:
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


	    break;


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
*   @function      declareFunction
*   @param         struct Program * p
*   @param         string *         name
*   @description
*/
struct Function * declareFunction(struct Program * p, string * name) {

    Dump("> Define Function");

    if (p == NULL) {
        ErrorException(ERROR_INTERN, "Parser :: Function Add :: Program is NULL");
    }

    if (!name->length) {
        ErrorException(ERROR_INTERN, "Parser :: Function Add :: ID is NULL");
    }

    struct Function * f = malloc( sizeof(struct Function));

    f->priority   = 0;
    f->parameters = new_tree(TREE_PLAIN);
    f->variables  = new_tree(TREE_PLAIN);

    strInit(&(f->name));
    strCopyString(&(f->name), name);

    tree_add(p->functions, name->str, f);

    return f;
}


/*
*   @function      declareFunctionParameter
*   @param         struct Function * f
*   @param         string *          name
*   @param         DataType          dType
*   @description
*/
void declareFunctionParameter(struct Function * f, string * name, DataType dType) {

    if (f == NULL || !name->length) {
        ErrorException(ERROR_INTERN, "Parser :: Add Parameter");
    }

    Dump("Define Function Param");

    struct DIM * var = declareParameter(name, dType);

    tree_add(f->parameters, name->str , var);
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


void getExpression(struct DIM * _return) {
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
                    LineErrorException(tok, ERROR_SYNTAX, "Exception LL");
                } else {
                    is_operator = isTokenOperator(tok.flag);
                }
            }
        }
    }


    if (!bracket_count) {
        LineErrorException(tok, ERROR_SYNTAX, "In Exception : Bracket");
    }

    _return->valueInteger = 3;
    _return->valueDouble  = 3.14;
    _return->valueString  = strChars("3.14");
}



///////////////////////////////////////////////////////////////////////////////////
//
//  DUMP PROGRAM
//


void _dumpFunctions(struct tree_node * node) {
    if (!node) return;
    _dumpFunctions(node->left);


    struct Function * f = node->payload;
    struct tree     * p = f->parameters;

    printf("Function(%s) %s\n", node->key, (f->name).str);

    _dumpParameters(p->root);

    printf("Return @%s\n\n", getDataTypeName(f->_return->dataType));

    _dumpFunctions(node->right);

    return;
}


void _dumpParameters(struct tree_node * node) {

    if (!node) return;

    _dumpParameters(node->left);

    struct DIM * var = node->payload;

    printf("  Parameter (%s) :: %s@%s\n", node->key, getDataTypeName(var->dataType), var->name.str);

    _dumpParameters(node->right);

    return;
}

void dumpFunctions(struct Program * p) {
    _dumpFunctions(p->functions->root);
}

void program_dump(struct Program * p) {
    printf("\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf(":: DUMP PROGRAM \n");
    printf("::\n:: SCOPE\n");

    printf("::\n:: FUNCTIONS::\n");
    dumpFunctions(p);
}

//void dumpFunctionParams(Function * fce) {}

