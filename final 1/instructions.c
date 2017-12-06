#include "instructions.h"
/*
*   @function      createVariable
*   @param         string * name
*   @param         string * value
*   @param         DataType dType
*   @param         DIMFrame frame
*   @description
*/

struct DIM * DIMInitReturn(DataType dType) {

    struct DIM * _return = malloc(sizeof(struct DIM));

    _return->dataType      = dType;
    _return->frame        = FRAME_RETURN;
    _return->valueInteger = 0;
    _return->valueDouble  = 0.0;
    _return->valueString  = strChars("");

    return  _return;
}

#define CHAR_OK(c) ((c) > 32 && \
(c) < 127 && \
(c) != '#' && \
(c) != '\\' )

/**
 * @brief Escapes string to string usable as IFJcode17 literal
 * @param s string to be escaped
 * @return new string with escaped unsafe characters
 */
static char *ifjcode_escape(const char *s)
{
	size_t len = 0;
	// Let's play it safe and use unsigned chars
	const unsigned char *us = (const unsigned char *) s;
	char *ret;
	size_t i, j;

	if (!s) {
		if (!(ret = calloc(1, sizeof(*ret))))
			ErrorException(ERROR_RUNTIME, "RUNTIME ERROR :: Allocation error");
		return ret;
	}

	for (i = 0; us[i]; i++) {
		if (CHAR_OK(us[i]))
			len += 1;
		else
			len += 4;
	}

	if (!(ret = calloc(len + 1, sizeof(*ret))))
		ErrorException(ERROR_RUNTIME, "RUNTIME ERROR :: Allocation error");

	for (i = 0, j = 0; us[i]; i++) {
		if (CHAR_OK(us[i])) {
			ret[j++] = us[i];
		} else {
			sprintf(&ret[j], "\\%03hhu", us[i]);
			j += 4;
		}
	}
	return ret;
}
#undef CHAR_OK


/*
*   @function      createVariable
*   @param         string * name
*   @param         string * value
*   @param         DataType dType
*   @param         DIMFrame frame
*   @description
*/
struct DIM * createVariable(string * name, string * value, DataType dType, DIMFrame frame) {

    if (!name->length) {
        ErrorException(ERROR_RUNTIME, "Create Variable :: NAME IS NULL");
    }

    struct DIM * variable = malloc(sizeof(struct DIM));

    strInit(&(variable->name));
    strCopyString(&(variable->name), name);

    variable->dataType = dType;
    variable->frame    = frame;

    if (value->length) {
        switch (dType) {

            case DATA_TYPE_INT: {
                variable->valueInteger = atoi(value->str);
            } break;

            case DATA_TYPE_DOUBLE: {
                char *ptr;
                variable->valueDouble  = strtod(value->str, &ptr);
            } break;

            case DATA_TYPE_STRING: {
                strInit(&(variable->valueString));
                strCopyString(&(variable->valueString), value);
            } break;

            default: {
                ErrorException(ERROR_INTERN, "Data Type is not defined");
            }
        }
    }

    return  variable;
}

void generateInstruction(list * commands, Instructions i, struct DIM * var1, struct DIM * var2, struct DIM * var3) {

    struct TWCode code = {
        .instr = i,
        .var1  = var1,
        .var2  = var2,
        .var3  = var3
    };

    list_append(commands, &code);
}


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

    char * label;
    char * var;
    char * sym1;
    char * sym2;

    switch(command.instr) {

        // NULL
        case I_CREATEFRAME:
        case I_PUSHFRAME:
        case I_POPFRAME:
        case I_CLEARS:
        case I_BREAK:
        case I_RETURN:
        case I_ADDS:
        case I_SUBS:
        case I_MULS:
        case I_DIVS:
        case I_LTS:
        case I_GTS:
        case I_EQS:
        case I_ANDS:
        case I_ORS:
        case I_NOTS:
            fprintf(f, "%s", getInstuctionName(command.instr));
            break;

        // LABEL
        case I_LABEL:
        case I_JUMP:
        case I_JUMPIFEQS:
        case I_JUMPIFNEQS:
            label = getLabel(command.var1);
            fprintf(f, "%s %s", getInstuctionName(command.instr), label);
            break;

        // VAR
        case I_DEFVAR:
        case I_POPS:
            var = getVar(command.var1);
            fprintf(f, "%s %s", getInstuctionName(command.instr), var);
            free(var);
            break;

        // SYMB
        case I_PUSHS:
        case I_WRITE:
        case I_DPRINT:
            sym1 = getSymb(command.var1);
            fprintf(f, "%s %s", getInstuctionName(command.instr), sym1);
            free(sym1);
            break;


        //** VAR TYPE
        case I_READ:
            var = getVar(command.var1);
            fprintf(f, "%s %s %s", getInstuctionName(command.instr), var, getDataTypeName(command.var1->dataType));
            free(var);
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
	case I_NOT:

            var  = getVar(command.var1);
            sym1 = getSymb(command.var2);

            fprintf(f, "%s %s %s", getInstuctionName(command.instr), var, sym1);

            free(var);
            free(sym1);
            break;

        // LABEL SYMB1 SYMB2
        case I_JUMPIFEQ:
        case I_JUMPIFNEQ:

            label = getLabel(command.var1);
            sym1  = getSymb(command.var2);
            sym2  = getSymb(command.var3);

            fprintf(f, "%s %s %s %s", getInstuctionName(command.instr), label, sym1, sym2);

            free(sym1);
            free(sym2);
        break;

        // VAR SYMB1 SYMB2
        case I_ADD:
        case I_SUB:
        case I_MUL:
        case I_DIV:
        case I_LT:
        case I_GT:
        case I_EQ:
        case I_AND:
        case I_OR:
        case I_STRI2INT:
        case I_GETCHAR:
        case I_SETCHAR:
        case I_CONCAT:

            var  = getVar(command.var1);
            sym1 = getSymb(command.var2);
            sym2 = getSymb(command.var3);

            fprintf(f, "%s %s %s %s", getInstuctionName(command.instr), var, sym1, sym2);

            free(var);
            free(sym1);
            free(sym2);
            break;
        default:
            ErrorException(ERROR_INTERN, "Invalid instruction.");
            break;
    }

    fprintf(f, "\n");
}


/*
*	@function getLabel
*	@param struct DIM * label
*	@description
*/
char * getLabel(struct DIM * label) {
    return (label->name).str;
}

/**
 * @function getLiteral
 * @brief creates string representing literal
 * @param sym symbol to be printed
 * @return new string representing literal
 */
char * getLiteral(struct DIM * sym) {
    char *buf;
    char *tmp;
    size_t sz;
    if (sym->frame != FRAME_CONST)
        ErrorException(ERROR_INTERN, "Not a literal");

    switch (sym->dataType) {
        case DATA_TYPE_BOOL:
            sz  = sizeof("bool@false");
            buf = (char *) malloc(sz);
            snprintf(buf, sz, "bool@%s", sym->valueInteger ? "true" : "false");
            break;
        case DATA_TYPE_INT:
            sz  = snprintf(NULL, 0, "int@%i", sym->valueInteger) + 1;
            buf = (char *) malloc(sz);
            sz  = snprintf(buf, sz, "int@%i", sym->valueInteger);
            break;
        case DATA_TYPE_DOUBLE:
            sz  = snprintf(NULL, 0, "float@%g", sym->valueDouble) + 1;
            buf = (char *) malloc(sz);
            sz  = snprintf(buf, sz, "float@%g", sym->valueDouble);
            break;
        case DATA_TYPE_STRING:
            tmp = ifjcode_escape(sym->valueString.str);
            sz  = snprintf(NULL, 0, "string@%s", tmp) + 1;
            buf = (char *) malloc(sz);
            sz  = snprintf(buf, sz, "string@%s", tmp);
            free(tmp);
            break;
        default:
            ErrorException(ERROR_INTERN, "Invalid data type");
    }

    return buf;
}

/*
*	@function getSymb
*	@param struct DIM * sym
*	@description
*/
char * getSymb(struct DIM * sym) {
    switch(sym->frame) {
        case FRAME_GLOBAL:
        case FRAME_LOCAL:
        case FRAME_TEMP:
            return getVar(sym);
            break;
        case FRAME_CONST:
            return getLiteral(sym);
        break;
        default: {
            ErrorException(ERROR_INTERN, "Invalid symbol");
        }
    }

    return NULL;
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
    switch(sym->frame) {
        case FRAME_GLOBAL:
        case FRAME_LOCAL:
        case FRAME_TEMP:
            sz  = snprintf(NULL, 0, "%s@%s", getFrameName(sym->frame), (sym->name).str);
            buf = (char *) malloc(sz + 1);
            snprintf(buf, sz+1, "%s@%s", getFrameName(sym->frame), (sym->name).str);
        break;
        default: {
            ErrorException(ERROR_INTERN, "Not a variable");
        }
    }

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
        case I_GT:           return "GT";
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
