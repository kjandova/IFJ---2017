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
// RESERVED WORDS:
//


// ASCII DEFINED
#define TOKEN_END_OF_FILE           -1  // EOF                                                                          

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

enum tokens {
          
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


//
// DATA TYPE
//

enum dataTypes {
    DATA_TYPE_INT, 	    // DataType Integer
    DATA_TYPE_DOUBLE, 	// DataType Double
    DATA_TYPE_STRING 	// DataType String
}
