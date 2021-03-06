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
//	@File				parser.h
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
//
//  PROGRAM STRUCT
//
//  Program
//     │
//     │
//     ├─ Scope                 ( struct fucntion)
//     │
//     ├─ Functions             ( struct fucntion)
//     │     │
//     │     ├─ Parameters      ( struct DIM)
//     │     │
//     │     ├─ Local Variables ( struct DIM)
//     │     │
//     │     ├─ Commands        ( struct TWCode)
//     │     │
//     │     └─ Return          ( struct DIM)
//     │
//     └─ [ Global Variables ]  ( struct DIM)


#ifndef IFJ_PARSER_H
#define IFJ_PARSER_H
////////////////////////////////////////////////////////
//
// Body of FUNCTION
//
struct Function {
    string            name;          // ID
    short int         priority;      // Priority
    list            * parameters;    //
    struct tree     * variables;
    list            * commands;
    struct DIM      * _return;
};

////////////////////////////////////////////////////////
//
// Body of Program
//
struct Program {
    struct Function * scope;
    struct tree     * functions;
    struct tree     * globalVariables;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Declare Parser Function
//
void              program_init(struct Program ** p);

// Subparsers
void parse_stmt_dim();
void parser_init_main_scope();

// FUNCTTIONS DECLARED
struct Function * functionDeclare(struct Program * p, string * name);
void              functionDeclareParameters(struct Function * f, string * name, DataType dType);

// FUNCTTIONS DEFINED
struct Function * functionDefine(struct Program * p, string * name);
void              functionDefineParameters(struct Function * f, string * name, DataType dType, int index);

struct DIM      * declareParameter(string * name, DataType dType);
struct DIM      * createVariable(string * name, string * value, DataType dType, DIMFrame frame);

// VARIABLES
struct DIM * searchVariable(struct Program * p, struct Function * f, string * name);
struct DIM * globalVariableExists(struct Program * p, string * name);
struct DIM * localVariableExists(struct Function * f, string * name);

void getExpression(struct DIM * _return);

void plumStackPush(int statType, int statMain);
int  plumStackPeek(int statType, int statMain);
int  plumStackPop();
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Declare Parser Dump
//
void program_dump(struct Program * p);

void dumpFunctions(struct Program * p);
void dumpParameters(struct Function * f);

#endif
