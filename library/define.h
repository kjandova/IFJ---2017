///////////////////////////////////////////////////////////////////////////////////
//
//	@Project 			IFJ 2017
//
//  @Authors
//  Jandová Krisnýna 	xjando04
//  Vilém Faigel		xfaige00
//  Nikola Timková		xtimko01
//	Bc. Váslav Doležal	xdolez76
//
//	@File				define.h
//	@Description		
//			
///////////////////////////////////////////////////////////////////////////////////


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
	SCANNER_WORD_END,
	SCANNER_COMMENT,
	SCANNER_COMMENT_TRY 	// Trying if comment is ending
};
      
//
// RESERVET WORDS:
//

//	TOKENS							start: 100
#define TOKEN_ID 					100 // ID   
#define TOKEN_END_OF_FILE 			101 // EOF

// OPERATORS						start: ASCII



#define TOKEN_MUL 					42  // *
#define TOKEN_ADD 					43  // +
#define TOKEN_SUB 					45  // -
#define TOKEN_DIV 					47  // /
#define TOKEN_LESS 					60  // <
#define TOKEN_EQUALS 				61  // =
#define TOKEN_MORE 					62  // >

#define TOKEN_EXCLAMATION_MARK		33  // !
#define TOKEN_DOUBLE_QUOTE			34  // "
#define TOKEN_QUOTE 				39  // '
#define TOKEN_SLASH					47  // /
#define TOKEN_BACKSLASH				92  // '\'

#define TOKEN_NON_EQUAL      		128 // <>
#define TOKEN_MORE_OR_EQUAL 		129 // >=
#define TOKEN_LESS_OR_EQUAL 		130 // <=


// CONSTRUCT TOKENS					start: 200
#define TOKEN_AS 					200
#define TOKEN_DIM 					201
#define TOKEN_DECLARE 				202
#define TOKEN_FUNCTION 				203
#define TOKEN_THEN 					204
#define TOKEN_END 					205
#define TOKEN_CONTINUE 				206
#define TOKEN_RETURN 				207
#define TOKEN_EXIT 					208
#define TOKEN_ASC 					209
#define TOKEN_SCOPE 				210	// MAIN FUNCTION

// VARIABLES						start: 220
#define TOKEN_DOUBLE 				220
#define TOKEN_INTEGER 				221
#define TOKEN_STRING 				222
#define TOKEN_SHARED 				223
#define TOKEN_STATIC 				224

// LOGIC OPERATIONS					start: 230
#define TOKEN_AND 					230
#define TOKEN_BOOLEAN 				231
#define TOKEN_NOT 					232
#define TOKEN_OR 					233

// BOOL								start: 235
#define TOKEN_TRUE 					235
#define TOKEN_FALSE 				236

// CONDITIONAL STATMENT				start: 240
#define TOKEN_IF 					240
#define TOKEN_ELSE 					241
#define TOKEN_ELSEIF 				242

// CYCLES							start: 245
#define TOKEN_DO 					246
#define TOKEN_WHILE 				247
#define TOKEN_FOR 					248
#define TOKEN_LOOP 					249

// FUNCTIONS						start: 255
#define TOKEN_INPUT 				255
#define TOKEN_PRINT 				256
#define TOKEN_SUBSTR 				257
#define TOKEN_LENGTH				258
#define TOKEN_CHR 					259

//
// DATE TYPE						start: 300
//
#define DATA_TYPE_INT 				300 // DataType Integer
#define DATA_TYPE_DOUBLE 			301 // DataType Double
#define DATA_TYPE_STRING 			302 // DataType String

#define TOKEN_NEXT 					303


//
// ERROR CODE
//

enum {
	SUCCESS	= 0,   		// Bez chyb
	ERROR_LEXICAL,  	// Lexikalni chyba
	ERROR_SYNTAX,   	// Syntakticka chyba
	ERROR_DEFINE,   	// Nedefinovana fce/prom, redefinace fce/prom
	ERROR_TYPE,     	// Typova nekompatibilita operace, spatny pocet param
	ERROR_CONVERT,  	// Chyba odvozovani datoveho typu
	ERROR_SEMANTIC, 	// Ostatni semanticke chyby
	ERROR_READ_NUM, 	// Chyba pri cteni cisla ze vstupu
	ERROR_UNINIT,   	// Prace s neinicializovanou prom
	ERROR_ZERO_DIV, 	// Deleni nuou
	ERROR_RUNTIME,      // Ostatni behove chyby
	ERROR_INTERN  =	99  // Interni chyba interpretu
};
