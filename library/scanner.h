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
//	@File				scanner.h
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>

//
// SCANNER STATES:
//

enum scanner {
	SCANNER_START = 1,
	SCANNER_DIGIT,
	SCANNER_WORD,
	SCANNER_EXCLAMATION_MARK,
	SCANNER_LINE_COMMENT,
	SCANNER_SLASH,
	SCANNER_BACKSLASH,
	SCANNER_LESS_THAN,
	SCANNER_MORE_THAN,

	SCANNER_FLOAT, 			// State as float (decimal point)
	SCANNER_EXPONENT_TRY, 	// Trying if exponent is right
	SCANNER_EXPONENT, 		// Ending exponential number
	SCANNER_STRING,
	SCANNER_ESCAPE_SEQUENCE,
	SCANNER_DECIMAL_CHAR,
	SCANNER_WORD_END,
	SCANNER_COMMENT,
	SCANNER_COMMENT_TRY 	// Trying if comment is ending
};

typedef struct {
	char * word;
	int token;
} Reserved;

Reserved reserved[35] = {
	{"AS", 			TOKEN_AS},
	{"ASC", 		TOKEN_ASC},
	{"DECLARE", 	TOKEN_DECLARE},
	{"DIM", 		TOKEN_DIM},
	{"DO", 			TOKEN_DO},
	{"DOUBLE", 		TOKEN_DOUBLE},
	{"ELSE", 		TOKEN_ELSE},
	{"END", 		TOKEN_END},
	{"CHR", 		TOKEN_CHR},
	{"FUNCTION", 	TOKEN_FUNCTION},
	{"IF", 			TOKEN_IF},
	{"INPUT", 		TOKEN_INPUT},
	{"INTEGER", 	TOKEN_INTEGER},
	{"LENGTH", 		TOKEN_LENGTH},
	{"LOOP", 		TOKEN_LOOP},
	{"PRINT", 		TOKEN_PRINT},
	{"RETURN", 		TOKEN_RETURN},
	{"SCOPE", 		TOKEN_SCOPE},
	{"STRING", 		TOKEN_STRING},
	{"SUBSTR", 		TOKEN_SUBSTR},
	{"THEN", 		TOKEN_THEN},
	{"WHILE", 		TOKEN_WHILE},
	{"AND", 		TOKEN_AND},
	{"BOOLEAN", 	TOKEN_BOOLEAN},
	{"CONTINUE", 	TOKEN_CONTINUE},
	{"ELSEIF", 		TOKEN_ELSEIF},
	{"EXIT", 		TOKEN_EXIT},
	{"FALSE", 		TOKEN_FALSE},
	{"FOR", 		TOKEN_FOR},
	{"NEXT", 		TOKEN_NEXT},
	{"NOT", 		TOKEN_NOT},
	{"OR", 			TOKEN_OR},
	{"SHARED", 		TOKEN_SHARED},
	{"STATIC", 		TOKEN_STATIC},
	{"TRUE", 		TOKEN_TRUE}
};


void scanner_init(char * path);
Token scanner_next_token();
int _scanner_next(string *word);
void scanner_token_dump(Token tok);

