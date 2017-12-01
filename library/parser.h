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


////////////////////////////////////////////////////////
//
// Body of FUNCTION
//
struct Function {
    string            name;          // ID
    short int         priority;      // Priority
    struct tree     * parameters;    //
    struct tree     * variables;
    struct tree     * commands;
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

struct Function * declareFunction(struct Program * p, string * name);
void              declareFunctionParameter(struct Function * f, string * name, DataType dType);

struct DIM      * declareParameter(string * name, DataType dType);
struct DIM      * createVariable(string * name, string * value, DataType dType, DIMFrame frame);


///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Declare Parser Dump
//
void program_dump(struct Program * p);

void dumpFunctions(struct Program * p);

void _dumpFunctions(struct tree_node * node);
void _dumpParameters(struct tree_node *node);


