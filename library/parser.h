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


///////////////////////
// DIM Frame

typedef enum  {
    FRAME_GLOBAL,
    FRAME_LOCAL,
    FRAME_TEMP,
    FRAME_PARAMETERS
} DIMFrame;


// Vytvoreni promenne
struct DIM {
    string              name;          // ID
    DIMFrame            frame;         // Frame
    short int           dataType;      // DT
    string              valueString;   // String
    int                 valueInteger;  // Integer
    double              valueDouble;   // Double
};

// Prikaz
typedef struct Command  TWCode;        // Three Way Code (instruction.h)

// Telo funkce
struct Function {
    string            name;          // ID
    short int         priority;      // Priority
    struct tree     * parameters;    //
    struct tree     * variables;
    struct tree     * commands;
    struct DIM      * _return;
};

struct Program {
    struct Function * scope;
    struct tree     * functions;
    struct tree     * globalVariables;
};

void              program_init(struct Program ** p);

struct Function * defFunction(struct Program * p, string * name);
void              defFunctionParameter(struct Function * f, string * name, DataType dType);

struct DIM      * defParameter(string * name, DataType dType);
struct DIM      * createVariable(string * name, string * value, DataType dType, DIMFrame frame);


void program_dump(struct Program * p);

void dumpFunctions(struct Program * p);

void _dumpFunctions(struct tree_node * node);
//void _dumpParameters(struct tree_node *node);


