typedef enum {
    DATA_TYPE_INT,                           // DataType Integer
    DATA_TYPE_DOUBLE, 	                     // DataType Double
    DATA_TYPE_STRING 	                     // DataType String
} DataType;

typedef enum {
   I_MOVE,
   I_CREATEFRAME, I_PUSHFRAME, I_POPFRAME,
   I_DEFVAR,
   I_RETURN,
   I_PUSHS,
   I_CLEARS,
   I_ADD,  I_SUB,  I_MUL,  I_DIV,
   I_ADDS, I_SUBS, I_MULS, I_DIVS,

   I_LT,  I_FT,   I_EQ,
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
    Instructions        instruction;
    struct DIM          * variable0;
    struct DIM          * variable1;
    struct DIM          * variable2;
};
