#include "instructions.h"


/*

void generateInstruction(struct stack ** commands, Instructions i, struct DIM * var1, struct DIM * var2, struct DIM * var3) {

    struct TWCode = {
        .instr = i,
        .var1  = var1,
        .var2  = var2,
        .var3  = var3
    };

    //stack_push(commands, &TWCode)
}


*/
/*
*	@function getDataTypeName
*	@param DataType DT
*	@description
*/
const char * getDataTypeName(DataType DT) {
    switch(DT) {
        case DATA_TYPE_VOID:   return "void";
        case DATA_TYPE_BOOL:   return "bool";
        case DATA_TYPE_INT:    return "int";
        case DATA_TYPE_DOUBLE: return "double";
        case DATA_TYPE_STRING: return "string";
    }

    ErrorException(ERROR_INTERN, "Is dont Data Type");
    return "";
}


/*
*	@function translateInstuctions
*	@param struct stack ** commands
*	@description
*/
/*void translateInstuctions(struct stack ** commands) {

}*/


/*
*	@function writeInstuction
*	@param FILE * f
*	@param struct TWCode command
*	@description Funkce vytvori novy retezec
*/
void writeInstuction(FILE * f, struct TWCode command) {

    switch(command.instr) {

        // NULL
        case I_CREATEFRAME:
        case I_PUSHFRAME:
        case I_POPFRAME:
        case I_CLEARS:
        case I_BREAK:
        case I_RETURN:
            fprintf(f, "%s", getInstuctionName(command.instr));
        break;

        // LABEL
        case I_LABEL:
        case I_JUMP:
        case I_JUMPIFEQS:
        case I_JUMPIFNEQS:
            fprintf(f, "%s %s", getInstuctionName(command.instr), getLabel(command.var1));
        break;

        // VAR
        case I_DEFVAR:
        case I_POPS:
            fprintf(f, "%s %s", getInstuctionName(command.instr), getVar(command.var1));
        break;

        // SYMB
        case I_PUSHS:
        case I_WRITE:
        case I_DPRINT:
            fprintf(f, "%s %s", getInstuctionName(command.instr), getSymb(command.var1));
        break;


        //** VAR TYPE
        case I_READ:
            fprintf(f, "%s\n", getInstuctionName(command.instr));
        break;
        // VAR SYMB
        case I_MOVE:
        case I_INT2FLOAT:
        case I_FLOAT2INT:
        case I_FLOAT2R2EINT:
        case I_FLOAT2R2OINT:
        case I_INT2CHAR:
        case I_STRLEN:
        case I_TYPE:
            fprintf(f, "%s %s %s \n", getInstuctionName(command.instr), getVar(command.var1), getSymb(command.var2));
        break;

        // LABEL SYMB1 SYMB2
        case I_JUMPIFEQ:
        case I_JUMPIFNEQ:
            fprintf(f, "%s %s %s \n", getInstuctionName(command.instr), getLabel(command.var1), getSymb(command.var2), getSymb(command.var3));
        break;

        // VAR SYMB1 SYMB2
        case I_ADD:
        case I_ADDS:
        case I_SUB:
        case I_SUBS:
        case I_MUL:
        case I_MULS:
        case I_DIV:
        case I_DIVS:
        case I_LT:
        case I_FT:
        case I_EQ:
        case I_LTS:
        case I_GTS:
        case I_EQS:
        case I_AND:
        case I_ANDS:
        case I_OR:
        case I_ORS:
        case I_NOT:
        case I_NOTS:
        case I_STRI2INT:
        case I_GETCHAR:
        case I_SETCHAR:
        case I_CONCAT:
             fprintf(f, "%s %s %s \n", getInstuctionName(command.instr), getVar(command.var1), getSymb(command.var2), getSymb(command.var3));
        break;
        default: break;
    }

    fprintf(f, "/n");
}


/*
*	@function getLabel
*	@param struct DIM * label
*	@description
*/
char * getLabel(struct DIM * label) {
    return (label->name).str;
}


/*
*	@function getSymb
*	@param struct DIM * sym
*	@description
*/
char * getSymb(struct DIM * sym) {
    char *buf;
    size_t sz;
    switch(sym->frame) {
        case FRAME_GLOBAL:
        case FRAME_LOCAL:
        case FRAME_TEMP:
            sz  = snprintf(NULL, 0, "%s@%s", getFrameName(sym->frame), (sym->name).str);
            buf = (char *) malloc(sz + 1);
            snprintf(buf, sz+1, "%s@%s", getFrameName(sym->frame), (sym->name).str);
        break;
        case FRAME_CONST:
            buf = getVar(sym);
        break;
        default: {
            ErrorException(ERROR_INTERN, "Invalid symbol");
        }
    }

    return buf;
}

const char *getFrameName(DIMFrame frame) {
    switch(frame) {
        case FRAME_GLOBAL: return "GF";
        case FRAME_LOCAL:  return "LF";
        case FRAME_TEMP:   return "TF";
        default: ErrorException(ERROR_INTERN, "Is not frame");
    }

    return "";
}


/*
*	@function getVar
*	@param struct DIM * sym
*	@description
*/
char * getVar(struct DIM * sym) {
    char *buf;
    size_t sz;

    sz  = snprintf(NULL, 0, "%s@%s", getDataTypeName(sym->dataType), (sym->name).str);
    buf = (char *) malloc(sz + 1);
    snprintf(buf, sz+1, "%s@%s", getDataTypeName(sym->dataType), (sym->name).str);

    return buf;
}


/*
*	@function getInstuctionName
*	@param Instructions instr
*	@description
*/
const char * getInstuctionName(Instructions instr) {
    switch(instr) {
        // NULL
        case I_CREATEFRAME:  return "CREATEFRAME";
        case I_PUSHFRAME:    return "PUSHFRAME";
        case I_POPFRAME:     return "POPFRAME";
        case I_CLEARS:       return "CLEARS";
        case I_BREAK:        return "BREAK";
        case I_RETURN:       return "RETURN";

        // LABEL
        case I_LABEL:        return "LABEL";

        case I_JUMP:         return "JUMP";
        case I_JUMPIFEQS:    return "JUMPIFEQS";
        case I_JUMPIFNEQS:   return "JUMPIFNEQS";

        // LABEL SYMB1 SYMB2
        case I_JUMPIFEQ:     return "JUMPIFEQ";
        case I_JUMPIFNEQ:    return "JUMPIFNEQ";

        // VAR
        case I_DEFVAR:       return "DEFVAR";
        case I_POPS:         return "POPS";

        // SYMB
        case I_PUSHS:        return "PUSHS";
        case I_WRITE:        return "WRITE";
        case I_DPRINT:       return "DPRINT";

        // VAR TYPE
        case I_READ:         return "READ";

        // VAR SYMB
        case I_MOVE:         return "MOVE";
        case I_INT2FLOAT:    return "INT2FLOAT";
        case I_FLOAT2INT:    return "FLOAT2INT";
        case I_FLOAT2R2EINT: return "FLOAT2R2EINT";
        case I_FLOAT2R2OINT: return "FLOAT2R2OINT";
        case I_INT2CHAR:     return "INT2CHAR";
        case I_STRLEN:       return "STRLEN";
        case I_TYPE:         return "TYPE";

        // VAR SYMB1 SYMB2
        case I_ADD:          return "ADD";
        case I_ADDS:         return "ADDS";
        case I_SUB:          return "SUB";
        case I_SUBS:         return "SUBS";
        case I_MUL:          return "MUL";
        case I_MULS:         return "MULS";
        case I_DIV:          return "DIV";
        case I_DIVS:         return "DIVS";

        case I_LT:           return "LT";
        case I_FT:           return "FT";
        case I_EQ:           return "EQ";
        case I_LTS:          return "LTS";
        case I_GTS:          return "GTS";
        case I_EQS:          return "EQS";
        case I_AND:          return "AND";
        case I_ANDS:         return "ANDS";
        case I_OR:           return "OR";
        case I_ORS:          return "ORS";
        case I_NOT:          return "NOT";
        case I_NOTS:         return "NOTS";

        case I_STRI2INT:     return "STRI2INT";

        case I_GETCHAR:      return "GETCHAR";
        case I_SETCHAR:      return "SETCHAR";

        case I_CONCAT:       return "CONCAT";

        default: ErrorException(ERROR_INTERN, "DEFAULT INSTRUCTION");
    }

    return "";
}
