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

// FUNCTTIONS DECLARED
struct Function * functionDeclare(struct Program * p, string * name);
void              functionDeclareParameters(struct Function * f, string * name, DataType dType);

// FUNCTTIONS DEFINED
struct Function * functionDefine(struct Program * p, string * name);
void              functionDefineParameters(struct Function * f, string * name, DataType dType, int index);

struct DIM      * declareParameter(string * name, DataType dType);
struct DIM      * createVariable(string * name, string * value, DataType dType, DIMFrame frame);

void getExpression(struct tree * commands, struct DIM * _return);

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Declare Parser Dump
//
void program_dump(struct Program * p);

void dumpFunctions(struct Program * p);
void dumpParameters(struct Function * f);

#endif
