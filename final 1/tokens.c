///////////////////////////////////////////////////////////////////////////////////
//
//	@Project 			IFJ 2017
//
//  @Authors
//  Krist�na Jandov�  	xjando04
//  Vil�m Faigel		xfaige00
//  Nikola Timkov�		xtimko01
//	Bc. V�clav Dole�al	xdolez76
//
//	@File				tokens.c
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////

#include "tokens.h"

const char* getTokenName(int flag) {
    switch (flag) {
        case TOKEN_END_OF_FILE:      return "EOF";
        case TOKEN_END_OF_LINE:      return "EOL";
        case DATA_TYPE_VOID:         return "DT_VOID";
        case DATA_TYPE_INT:          return "DT_INT";
        case DATA_TYPE_DOUBLE:       return "DT_DOUBLE";
        case DATA_TYPE_STRING:       return "DT_STRING";
        case TOKEN_MUL:              return "T_MUL";
        case TOKEN_ADD:              return "T_ADD";
        case TOKEN_SUB:              return "T_SUB";
        case TOKEN_DIV:              return "T_SLASH"; // DIV or SLASH '/'
        case TOKEN_LESS:             return "T_LESS";
        case TOKEN_EQUALS:           return "T_EQUALS";
        case TOKEN_MORE:             return "T_MORE";
        case TOKEN_EXCLAMATION_MARK: return "T_EXCLAMATION_MARK";
        case TOKEN_DOUBLE_QUOTE:     return "T_DOUBLE_QUOTE";
        case TOKEN_QUOTE:            return "T_QUOTE";
        case TOKEN_SEMICOLON:        return "T_SEMICOLON";
        case TOKEN_COMMA:            return "T_COMMA";
        case TOKEN_BACKSLASH:        return "T_BACKSLASH";
        case TOKEN_NON_EQUAL:        return "T_NON_EQUAL";
        case TOKEN_MORE_OR_EQUAL:    return "T_MORE_OR_EQUAL";
        case TOKEN_LESS_OR_EQUAL:    return "T_LESS_OR_EQUAL";
        case TOKEN_BRACKET_RIGHT:    return "T_BRACKET_RIGHT";
        case TOKEN_BRACKET_LEFT:     return "T_BRACKET_LEFT";
        case TOKEN_ID:               return "T_ID";
        case TOKEN_AS:               return "T_AS";
        case TOKEN_DIM:              return "T_DIM";
        case TOKEN_DECLARE:          return "T_DECLARE";
        case TOKEN_FUNCTION:         return "T_FUNCTION";
        case TOKEN_THEN:             return "T_THEN";
        case TOKEN_END:              return "T_END";
        case TOKEN_CONTINUE:         return "T_CONTINUE";
        case TOKEN_RETURN:           return "T_RETURN";
        case TOKEN_EXIT:             return "T_EXIT";
        case TOKEN_SCOPE:            return "T_SCOPE";
        case TOKEN_DOUBLE:           return "T_DOUBLE";
        case TOKEN_INTEGER:          return "T_INTEGER";
        case TOKEN_STRING:           return "T_STRING";
        case TOKEN_SHARED:           return "T_SHARED";
        case TOKEN_STATIC:           return "T_STATIC";
        case TOKEN_AND:              return "T_AND";
        case TOKEN_BOOLEAN:          return "T_BOOLEAN";
        case TOKEN_NOT:              return "T_NOT";
        case TOKEN_OR:               return "T_OR";
        case TOKEN_TRUE:             return "T_TRUE";
        case TOKEN_FALSE:            return "T_FALSE";
        case TOKEN_IF:               return "T_IF";
        case TOKEN_ELSE:             return "T_ELSE";
        case TOKEN_ELSEIF:           return "T_ELSEIF";
        case TOKEN_DO:               return "T_DO";
        case TOKEN_WHILE:            return "T_WHILE";
        case TOKEN_FOR:              return "T_FOR";
        case TOKEN_LOOP:             return "T_LOOP";
        case TOKEN_NEXT:             return "T_NEXT";
        case TOKEN_INPUT:            return "T_INPUT";
        case TOKEN_PRINT:            return "T_PRINT";
        case TOKEN_SUBSTR:           return "T_SUBSTR";
        case TOKEN_LENGTH:           return "T_LENGTH";
        case TOKEN_CHR:              return "T_CHR";
        case TOKEN_ASC:              return "T_ASC";
    }

    return "TOKEN_DEFAULT";
}

int getDataTypeFromToken(int flag) {

    switch(flag) {
        case TOKEN_BOOLEAN: return DATA_TYPE_BOOL;
        case TOKEN_INTEGER: return DATA_TYPE_INT;
        case TOKEN_DOUBLE:  return DATA_TYPE_DOUBLE;
        case TOKEN_STRING:  return DATA_TYPE_STRING;
    }

    return -1;
}

int isTokenOperator(int flag) {
	switch(flag) {
		//ARYTHMETIC
		case TOKEN_ADD:			    // +
		case TOKEN_SUB:			    // -
		case TOKEN_MUL:			    // *
		case TOKEN_DIV:			    // /
		case TOKEN_BACKSLASH:       // \.
		// COMPARISON
		case TOKEN_LESS: 			// <
		case TOKEN_MORE:			// >
		case TOKEN_LESS_OR_EQUAL:	// <=
		case TOKEN_MORE_OR_EQUAL:	// >=
		case TOKEN_EQUALS:			// =
		case TOKEN_NON_EQUAL:		// <>
			return 1;
	}

	return 0;
}

int isTokenID(int type) {
	switch(type) {
		case DATA_TYPE_INT:
		case DATA_TYPE_DOUBLE:
		case DATA_TYPE_STRING:
		case TOKEN_ID:
		return 1;
	}

	return 0;
}
