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

    // FUNCTION (ID) ( <PARAM> ) AS <TYPE> EOL
    PARSER_SCOPE_START,
    PARSER_SCOPE_STATMENTS,
    PARSER_SCOPE_END,

    //
    // IF <EXPRESSION> THEN EOL <STATEMENT_LIST> <ELSEIF> <ELSE> END IF
    PARSER_STATMENT_IF,
    PARSER_STATMENT_IF_ELSE,
    PARSER_STATMENT_IF_END,

    //
    // DO WHILE <EXPRESSION> EOL <STATEMENT_LIST> <LOOP>
    PARSER_STATMENT_WHILE,
    PARSER_STATMENT_WHILE_END,

    PARSER_STATMENT_END,
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


struct Program  * __parser_program;  // GLOBAL PROGRAM
struct Function * __parser_function; // FUNCTION TEMP VARIABLE
Token             tok;
stack           * pStack;
int               pIter;
/*
*   @function      parser_init
*   @param         char * fileNameSource
*   @description
*/
void parser_init(char * fileNameSource) {

    scanner_init(fileNameSource);
    program_init(&__parser_program);

}

#define STAT_FUNCTION 0
#define STAT_IF       1
#define STAT_WHILE    2
#define STAT_SCOPE    3

/*
*   @function      parser_run
*   @description
*/

struct plumStat {
    int statIter;
    int statMain;
    int statType;
} plumStat;

void parser_run() {

    int stateMain   = PARSER_START,
        stateReturn = PARSER_START;

    int dType,
        counterDefineParams = 0;

    NEW(pStack);
    stack_new(pStack, sizeof(plumStat));


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
                    case TOKEN_SCOPE:
                        parser_init_main_scope();
                        plumStackPush(STAT_SCOPE, PARSER_SCOPE_END);
                        stateMain = PARSER_SCOPE_STATMENTS;
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
                __parser_function = functionDeclare(__parser_program, &(tok.ID));
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

                __parser_function->_return = _return;

                Dump("> DECLARE Function %s() return@%s\n", (__parser_function->name).str, getDataTypeName(_return->dataType));

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
                __parser_function = functionDefine(__parser_program, &(tok.ID));
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

                plumStackPush(STAT_FUNCTION, PARSER_DEFINE_FUNCTION_END);
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

                if (__parser_function->_return->dataType != _return->dataType) {
                    LineErrorException(tok, ERROR_LEXICAL, "Return in function %s() an '%s' type was specified, the '%s' data type is expected",
                                   (__parser_function->name).str, getDataTypeName(__parser_function->_return->dataType), getDataTypeName(_return->dataType)
                    );
                }

                __parser_function->_return = _return;

                Dump("> DEFINE Function %s() return@%s\n", (__parser_function->name).str, getDataTypeName(_return->dataType));

                stateMain = PARSER_DEFINE_FUNCTION_STATMENTS;

            } break;

            case PARSER_SCOPE_STATMENTS:
            case PARSER_DEFINE_FUNCTION_STATMENTS: {

                switch (tok.flag) {

                    // DIM <ID> AS <DT> [= <expression> ]
                    case TOKEN_DIM:
                        parse_stmt_dim();
                    break;

                    // IF <expression> THEN EOL <statment_list>
                    case TOKEN_IF:
                        stateMain = PARSER_STATMENT_IF;
                    break;

                    // ELSE <statment_list>
                    case TOKEN_ELSE:
                        stateMain = PARSER_STATMENT_IF_ELSE;
                    break;

                    // DO
                    case TOKEN_DO:
                        stateMain = PARSER_STATMENT_WHILE;
                    break;

                    // END LOOP
                    case TOKEN_END:
                    case TOKEN_LOOP:
                        stateMain = plumStackPop(); // Zasobni pro vnoření počínaje funkcí [fce, if, if, while,...]
                    break;

                    // EOF
                    case TOKEN_END_OF_FILE:
                        LineErrorException(tok, ERROR_SYNTAX, "End of file while processing FUNCTION");
                    break;

                    default:
                        tok = scanner_next_token();
                    break;
                }
            } break;

            case PARSER_DEFINE_FUNCTION_END: {
                tok = scanner_next_token();

                if (tok.flag != TOKEN_FUNCTION) {
                    LineErrorException(tok, ERROR_SYNTAX, "FUNCTION is missing");
                }

                Dump("> DEFINE Function %s() COMPLETE\n", (__parser_function->name).str);

                stateMain   = PARSER_START;
            } break;
            case PARSER_SCOPE_END: {
                tok = scanner_next_token();

                if (tok.flag != TOKEN_SCOPE) {
                    LineErrorException(tok, ERROR_SYNTAX, "SCOPE is missing");
                }

                Dump("> DEFINE Scope COMPLETE\n");

                stateMain   = PARSER_START;
            } break;

            ///////////////////////////////////////////////////////////////////////
            // IF <extension> THEN EOL <statments> ELSE <statmens> END IF
            //
            case PARSER_STATMENT_IF: {

                // IF <extension>

                // Call getExpression
                struct DIM * _return   = malloc(sizeof(struct DIM));

                string result = strPrintf("IF_%d_result", pIter);

                _return->name     = result;
                _return->dataType = DATA_TYPE_INT;

                ////////////////////////////////////////////
                // <expressionBlock>
                //
                // EXPRESSION
                getExpression(_return);

                if (tok.flag != TOKEN_THEN) {
				    LineErrorException(tok, ERROR_SYNTAX, "THEN is missing");
				}

				///////////////////////////////////////////////////////////////////////////////////
				//
                // JUMPIFNEQ IF_[i]_true LF@result int@0
                // JUMP      IF_[i]_false
                // LABEL     IF_[i]_true

                // string       label;
                // struct DIM * labelT;
                // struct DIM * labelF;

                // label   = strPrintf("IF_%d_true", pIter);
                // labelT  = createDIMLabel(label);

                // label   = strPrintf("IF_%d_false", pIter);
                // labelF  = createDIMLabel(label);

                // generateInstruction(__parser_function->commands, I_JUMPIFNEQ, labelT, _return, NULL);
                // generateInstruction(__parser_function->commands, I_JUMP     , labelF, NULL   , NULL);
                // generateInstruction(__parser_function->commands, LABEL      , labelT, NULL   , NULL);
                //
                // free(label);
                ///////////////////////////////////////////////////////////////////////////////////

                plumStackPush(STAT_IF, PARSER_STATMENT_IF_ELSE);

                stateMain = PARSER_DEFINE_FUNCTION_STATMENTS;
            } break;

            case PARSER_STATMENT_IF_ELSE: {

                int i = plumStackPeek(STAT_IF, PARSER_STATMENT_IF_END);

                ///////////////////////////////////////////////////////////////////////////////////
                // JUMP      IF_[i]_end
                // LABEL     IF_[i]_false
                //

                // string       label;
                // struct DIM * labelF;
                // struct DIM * labelE;

                // label   = strPrintf("IF_%d_false", i);
                // labelF  = createDIMLabel(label);

                // label   = strPrintf("IF_%d_end", i);
                // labelE  = createDIMLabel(label);

                // generateInstruction(__parser_function->commands, I_JUMP    , labelE, NULL   , NULL);
                // generateInstruction(__parser_function->commands, LABEL     , labelF, NULL   , NULL);
                //
                // free(label);
                unused(i);
                stateMain = PARSER_DEFINE_FUNCTION_STATMENTS;

                // <commandsBlock>
            } break;

            case PARSER_STATMENT_IF_END: {

                tok = scanner_next_token();
				if (tok.flag != TOKEN_IF) {
				    LineErrorException(tok, ERROR_SYNTAX, "END >IF< is missing");
				}

				tok = scanner_next_token();
				if (tok.flag != TOKEN_END_OF_LINE) {
				    LineErrorException(tok, ERROR_SYNTAX, "after THEN must be end of line");
				}

				///////////////////////////////////
                //
                // LABEL  IF_[i]_end
                //

                // string       label;
                // struct DIM * labelE;

                // label   = strPrintf("IF_%d_end", pIter);
                // labelE  = createDIMLabel(label);

                // generateInstruction(__parser_function->commands, LABEL     , labelF, NULL   , NULL);
                //
                // free(label);

				stateMain = PARSER_DEFINE_FUNCTION_STATMENTS;

            break;

		/////////////////////////////////
		// Print label instruction
		/////////////////////////////////
		}


            ///////////////////////////////////////////////////////////////////////
            // DO WHILE <expression> EOL
            // LOOP
            case PARSER_STATMENT_WHILE: {

                // DO >WHILE< <extension>
		        tok = scanner_next_token();
		        if (tok.flag != TOKEN_WHILE) {
		            LineErrorException(tok, ERROR_SYNTAX, "WHILE is missing");
		        }


                // Call getExpression
                struct DIM * _return   = malloc(sizeof(struct DIM));
                string        result   = strPrintf("result", pIter);

                _return->name     = result;
                _return->dataType = DATA_TYPE_INT;

		        //////////////////////////////////////////////////////////////////////////////////
				//
                // LABEL     WHILE_[i]_start LF@result int@0

                // string    label;

                // label     = strPrintf("WHILE_%d_start", pIter);
                // struct DIM * labelS = createDIMLabel(label);

                // generateInstruction(__parser_function->commands, LABEL     , labelT, NULL   , int@0);
                //
                ///////////////////////////////////////////////////////////////////////////////////

                ///////////////////////////////////////////////////////////////////////////////////
                //
                // EXPRESSION

                getExpression( _return);

                ///////////////////////////////////////////////////////////////////////////////////
				//
                // JUMPIFEQ IF_[i]_end LF@result int@0

                // label   = strPrintf("WHILE_%d_end", pIter);
                // struct DIM * labelE = createDIMLabel(label);

                // generateInstruction(__parser_function->commands, I_JUMPIFEQ, labelE, _return, int@0);
                //
                ///////////////////////////////////////////////////////////////////////////////////

                plumStackPush(STAT_WHILE, PARSER_STATMENT_WHILE_END);

                stateMain = PARSER_DEFINE_FUNCTION_STATMENTS;
            } break;

            ///////////////////////////////////////////////////////////////////////
            // DO WHILE <expression> EOL
            // LOOP
            case PARSER_STATMENT_WHILE_END: {

                if (tok.flag != TOKEN_LOOP) {
                    LineErrorException(tok, ERROR_SYNTAX, "WHILE is missing");
                }

                ///////////////////////////////////////////////////////////////////////////////////
				//
                // LABEL IF_[i]_end

                // label   = strPrintf("WHILE_%d_end", pIter);
                // struct DIM * labelE = createDIMLabel(label);

                // generateInstruction(__parser_function->commands, I_LABEL, labelE, NULL, NULL);
                //
                ///////////////////////////////////////////////////////////////////////////////////
                stateMain = PARSER_DEFINE_FUNCTION_STATMENTS;
            } break;

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
                    switch(stateReturn) {
                        case PARSER_DECLARE_FUNCTION_END:     functionDeclareParameters(__parser_function, &tmpID, dType); break;
                        case PARSER_DEFINE_FUNCTION_RETURN:  functionDefineParameters(__parser_function, &tmpID, dType, counterDefineParams); break;
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

    //program_dump(__parser_program);
    writeProgram(stdout, __parser_program);
    exit(0);
}


void plumStackPush(int statType, int statMain) {

    struct plumStat plum = {
        .statIter = pIter++,
        .statMain = statMain,
        .statType = statType
    };

    stack_push(pStack, &plum);
}


int plumStackPeek(int statType, int statMain) {

    struct plumStat plum;

    stack_peek(pStack, (void*) &plum);

    if (plum.statType != statType) {
        LineErrorException(tok, ERROR_SYNTAX, "ENDING STATMENT BLOCK");
    }

    plum.statMain = statMain;

    return plum.statIter;
}

int plumStackPop() {

    struct plumStat plum;

    stack_pop(pStack, (void*) &plum);

    return plum.statMain;
}

struct DIM * createDIMLabel(string * name) {
    struct DIM * label = malloc(sizeof(struct DIM));
    strCopyString(&label->name, name);
    return label;
}

void parser_init_main_scope()
{
    if (__parser_program->scope)
        LineErrorException(tok, ERROR_DEFINE, "Trying to redefine scope");

    NEW(__parser_program->scope);
    __parser_function = __parser_program->scope;
    __parser_function->name = strChars("&main");
    __parser_function->parameters = NULL;
    NEW(__parser_function->variables);
    tree_init(__parser_function->variables, TREE_PLAIN);
    NEW(__parser_function->commands);
    list_new(__parser_function->commands, sizeof(struct TWCode));
    __parser_function->_return = NULL;
}

void parse_stmt_dim()
{
    struct DIM *var;
    NEW(var);
    strInit(&var->name);
    var->frame = FRAME_LOCAL;
    // >DIM< id AS type [ = expr ] EOL
    // DIM >id< AS type [ = expr ] EOL
    tok = scanner_next_token();
    if (tok.flag != TOKEN_ID)
        LineErrorException(tok, ERROR_SYNTAX, "ID of variable is missing");

    strCopyString(&var->name, &tok.ID);
    // DIM id >AS< type [ = expr ] EOL
    tok = scanner_next_token();
    if (tok.flag != TOKEN_AS)
        LineErrorException(tok, ERROR_SYNTAX, "AS is missing");

    // DIM id AS >type< [ = expr ] EOL
    tok = scanner_next_token();
    if ((var->dataType = getDataTypeFromToken(tok.flag)) == -1)
        LineErrorException(tok, ERROR_SYNTAX, "type of variable is missing");

    // DIM id AS type [ >=< expr ] EOL
    tok = scanner_next_token();
    if (tok.flag == TOKEN_EQUALS) {
        // DIM id AS type [ = >expr< ] EOL
        getExpression(var);
    }

    // DIM id AS type [ = expr ] >EOL<
    if (tok.flag != TOKEN_END_OF_LINE)
        LineErrorException(tok, ERROR_SYNTAX, "Garbage after variable definition");

    // Test for id collision w/fns and try to add variable
    if (tree_get(__parser_program->functions, var->name.str, NULL) ||
        localVariableExists(__parser_function, &var->name))
        LineErrorException(tok, ERROR_DEFINE, "Name already used");

    tree_add(__parser_function->variables, var->name.str, var);
    Dump("> DEFINE variable %s COMPLETE\n", var->name.str);
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
//  VARIABLES
//

/*
*   @function      searchVariable
*   @param         struct Program * p
*   @param         struct Function * f
*   @param         string * name
*   @description
*/
struct DIM * searchVariable (struct Program * p, struct Function * f, string * name) {
    struct DIM * variable = localVariableExists(f, name);
    if (variable) return variable;
    return globalVariableExists(p, name);
}

/*
*   @function      globalVariableExists
*   @param         struct Program * p
*   @param         string * name
*   @description
*/
struct DIM * globalVariableExists(struct Program * p, string * name) {

    struct tree * vars = p->globalVariables;

    if (!name || !(name->length)) {
        ErrorException(ERROR_INTERN, "variables isnt null");
    }

    struct DIM * variable;

    tree_get(vars, name->str, (void *) &variable);

    return variable;
}


/*
*   @function      localVariableExists
*   @param         struct Function * f
*   @param         string * name
*   @description
*/
struct DIM * localVariableExists(struct Function * f, string * name) {

    struct tree * vars   = f->variables;
    list        * params = f->parameters;

    if (!f || !name || !(name->length)) {
        ErrorException(ERROR_INTERN, "variables isnt null");
    }

    struct DIM * variable = NULL;

    tree_get(vars, name->str, (void *) &variable);

    if (variable) return variable;

    for(int i = 0; i < list_size(params); i++) {
        variable = list_index(params, i);
        if (!strCmpString(&variable->name, name)) {
            return variable;
        }
    }

    return NULL;
}


///////////////////////////////////////////////////////////////////////////////////
//
//  EXPRESION
//

void getExpression(struct DIM * _return) {

    Dump("Expression");

    tok = scanner_next_token();
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

    unused(__parser_function->commands);

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

