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
//     ├─ [ Global Variables ]  ( struct DIM)
//     │
//     ├─ Scope                 ( struct fucntion)
//     │
//     ├─ Functions             ( struct fucntion)
//     │     │
//     │     ├─ Parameters      ( struct fucntion)
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
// DIM ( Memmory )
//

// Memmomry Frames
typedef enum  {
    FRAME_GLOBAL,
    FRAME_LOCAL,
    FRAME_TEMP,
    FRAME_PARAMETERS
} DIMFrame;


// Memmory struct
struct DIM {
    string              name;          // ID
    DIMFrame            frame;         // Frame
    short int           dataType;      // DT
    string              valueString;   // String
    int                 valueInteger;  // Integer
    double              valueDouble;   // Double
};

////////////////////////////////////////////////////////
//
// Command Three Way Code (instruction.h)
//
typedef struct Command  TWCode;




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

struct Function * defFunction(struct Program * p, string * name);
void              defFunctionParameter(struct Function * f, string * name, DataType dType);

struct DIM      * defParameter(string * name, DataType dType);
struct DIM      * createVariable(string * name, string * value, DataType dType, DIMFrame frame);


///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Declare Parser Dump
//
void program_dump(struct Program * p);

void dumpFunctions(struct Program * p);

void _dumpFunctions(struct tree_node * node);
void _dumpParameters(struct tree_node *node);


