#ifndef IFJ_INSTRUCTIONS_H
#define IFJ_INSTRUCTIONS_H


////////////////////////////////////////////////////////
//
// DIM ( Memmory )
//

// Memmomry Frames
typedef enum  {
    FRAME_GLOBAL,
    FRAME_LOCAL,
    FRAME_TEMP,
    FRAME_PARAMETERS,
    FRAME_RETURN,
    FRAME_CONST
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

typedef enum {
   I_MOVE,
   I_CREATEFRAME, I_PUSHFRAME, I_POPFRAME,
   I_DEFVAR,
   I_RETURN,
   I_POPS,
   I_PUSHS,
   I_CLEARS,
   I_ADD,  I_SUB,  I_MUL,  I_DIV,
   I_ADDS, I_SUBS, I_MULS, I_DIVS,

   I_LT,  I_GT,   I_EQ,
   I_LTS, I_GTS,  I_EQS,

   I_AND,  I_OR,  I_NOT,
   I_ANDS, I_ORS, I_NOTS,

   I_INT2FLOAT,     I_FLOAT2INT,
   I_INT2FLOATS,    I_FLOAT2INTS,

   I_FLOAT2R2EINT,  I_FLOAT2R2OINT,
   I_FLOAT2R2EINTS, I_FLOAT2R2OINTS,

   I_INT2CHAR,      I_STRI2INT,
   I_INT2CHARS,     I_STRI2INTS,

   I_READ,
   I_WRITE,

   I_CONCAT,
   I_STRLEN,

   I_GETCHAR,
   I_SETCHAR,

   I_TYPE,
   I_LABEL,
   I_JUMP,
   I_JUMPIFEQ,   I_JUMPIFNEQ,
   I_JUMPIFEQS,  I_JUMPIFNEQS,
   I_BREAK,
   I_DPRINT
} Instructions;

struct TWCode {
    Instructions        instr;
    struct DIM          *var1;
    struct DIM          *var2;
    struct DIM          *var3;
};


void generateInstruction(stack * commands, Instructions i, struct DIM * var1, struct DIM * var2, struct DIM * var3);
//void translateInstuctions(struct stack ** commands);
struct DIM * DIMInitReturn(DataType dType);
void writeInstuction(FILE * f, struct TWCode command);
char * getLabel(struct DIM * label);
char * getSymb(struct DIM * sym);
char * getVar(struct DIM * sym);
const char * getInstuctionName(Instructions instr);
const char * getFrameName(DIMFrame frame);

#endif // IFJ_INSTRUCTIONS_H
