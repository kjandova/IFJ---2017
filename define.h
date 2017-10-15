//states for scanner:
#define START 1
#define DIGIT 2
#define WORD 3 
#define EXCLAMATION_MARK 4
#define LINE_COMMENT 5
#define SLASH 6
#define BACKSLASH 7
#define LESS_THAN 8
#define MORE_THAN 9

#define FLOAT 10 // state as float (decimal point) 
#define EXPONENT_TRY 11 //trying if exponent is right 
#define EXPONENT 12 //ending exponential number
#define STRING 13
#define WORD_END 14
#define COMMENT 15
#define COMMENT_TRY 16 //trying if comment is ending


//operarors
#define TOKEN_EQUALS 100
#define TOKEN_ADD 101        // +
#define TOKEN_SUB 102     // -
#define TOKEN_MUL 103  // *
#define TOKEN_DIV 104        // /
#define TOKEN_MORE_THAN 105            // >
#define TOKEN_LESS_THAN 106 // <
#define TOKEN_MORE_THAN_OR_EQUAL 107   // >=
#define TOKEN_LESS_THAN_OR_EQUAL 108 //<=



//integer value (C-int)
#define TOKEN_INT 113

//double in source file
#define TOKEN_DOUBLE_N 114 


//ID
#define TOKEN_ID 109         

//string in source file
#define TOKEN_STRING_N 134

//reserved words:
#define TOKEN_AS 200
#define TOKEN_ASC 201
#define TOKEN_DECLARE 202
#define TOKEN_DIM 203
#define TOKEN_DO 204
#define TOKEN_DOUBLE 205
#define TOKEN_ELSE 206
#define TOKEN_END 207
#define TOKEN_CHR 208
#define TOKEN_FUNCTION 209
#define TOKEN_IF 210
#define TOKEN_INPUT 211
#define TOKEN_INTEGER 212
#define TOKEN_LENGTH 213
#define TOKEN_LOOP 214
#define TOKEN_PRINT 215
#define TOKEN_RETURN 216
#define TOKEN_SCOPE 217
#define TOKEN_STRING 218
#define TOKEN_SUBSTR 219
#define TOKEN_THEN 220
#define TOKEN_WHILE 221
#define TOKEN_AND 222
#define TOKEN_BOOLEAN 223
#define TOKEN_CONTINUE 224
#define TOKEN_ELSEIF 225
#define TOKEN_EXIT 226
#define TOKEN_FALSE 227
#define TOKEN_FOR 228
#define TOKEN_NEXT 229
#define TOKEN_NOT 230
#define TOKEN_OR 231
#define TOKEN_SHARED 232
#define TOKEN_STATIC 233
#define TOKEN_TRUE 234


//EOF
#define TOKEN_END_OF_FILE 126 


//error codes

#define LEXICAL_ERROR	1  //lexikalni chyba
#define SYNTAX_ERROR	2  //syntakticka chyba
#define DEFINE_ERROR	3  //nedefinovana fce/prom, redefinace fce/prom
#define TYPE_ERROR	4  //typova nekompatibilita operace, spatny pocet param
#define CONVERT_ERROR	5  //chyba odvozovani datoveho typu
#define SEMANTIC_ERROR	6  //ostatni semanticke chyby
#define READ_NUM_ERROR	7  //chyba pri cteni cisla ze vstupu
#define UNINIT_ERROR	8  //prace s neinicializovanou prom
#define ZERO_DIV_ERROR	9  //deleni nuou
#define RUNTIME_ERROR	10 //ostatni behove chyby
#define INTERN_ERROR	99 //interni chyba interpretu
#define SUCCESS		0  //bez chyb


#define SYNTAX_OK 0
#define SEM_ERROR SEMANTIC_ERROR
// Vedlejsi potreby parseru
#define MAX_SIZE 20 
#define OTHER 871
#define ERR	  872

