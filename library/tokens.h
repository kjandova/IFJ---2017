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
//	@File				define.h
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////


//
// TOKENS
//


enum tokens {

    TOKEN_END_OF_FILE             = -1,  // EOF

    // DATA TYPE
    DATA_TYPE_INT                 = 0, 	 // DataType Integer
    DATA_TYPE_DOUBLE, 	                 // DataType Double
    DATA_TYPE_STRING, 	                 // DataType String

    // ASCII DEFINED
    TOKEN_MUL 					  = 42,  // *
    TOKEN_ADD 					  = 43,  // +
    TOKEN_SUB 					  = 45,  // -
    TOKEN_DIV 			          = 47,  // /
    TOKEN_LESS 					  = 60,  // <
    TOKEN_EQUALS                  = 61,  // =
    TOKEN_MORE 					  = 62,  // >

    TOKEN_EXCLAMATION_MARK		  = 33,  // !
    TOKEN_DOUBLE_QUOTE			  = 34,  // "
    TOKEN_QUOTE 				  = 39,  // '
    TOKEN_SLASH					  = 47,  // /
    TOKEN_BACKSLASH				  = 92,  // '\'

    TOKEN_NON_EQUAL      		  = 128, // <>
    TOKEN_MORE_OR_EQUAL 		  = 129, // >=
    TOKEN_LESS_OR_EQUAL 		  = 130, // <=

    // RESERVED WORDS:
    TOKEN_ID 					  = 200,
    TOKEN_AS,
    TOKEN_DIM,
    TOKEN_DECLARE,
    TOKEN_FUNCTION,
    TOKEN_THEN,
    TOKEN_END,
    TOKEN_CONTINUE,
    TOKEN_RETURN,
    TOKEN_EXIT,
    TOKEN_SCOPE, // MAIN FUNCTION

    // VARIABLES
    TOKEN_DOUBLE,
    TOKEN_INTEGER,
    TOKEN_STRING,
    TOKEN_SHARED,
    TOKEN_STATIC,

    // LOGIC OPERATIONS
    TOKEN_AND,
    TOKEN_BOOLEAN,
    TOKEN_NOT,
    TOKEN_OR,

    // BOOL
    TOKEN_TRUE,
    TOKEN_FALSE,

    // CONDITIONAL STATMENT
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_ELSEIF,

    // CYCLES
    TOKEN_DO,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_LOOP,
    TOKEN_NEXT,

    // FUNCTIONS
    TOKEN_INPUT,
    TOKEN_PRINT,
    TOKEN_SUBSTR,
    TOKEN_LENGTH,
    TOKEN_CHR,
    TOKEN_ASC
};


const char * getTokenName(int flag);
