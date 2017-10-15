#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>

#include "scanner.h"

FILE * file;

void set_source_file(FILE *f) {
    file = f;
}

int get_next_token(string *word){
	
	char c;
	
	strClear(word);
	
	int state = SCANNER_START;	//because start
	
	while(1) {
		c = getc(file);
		switch(state){
			case SCANNER_START: //every new statement 
				if(isspace(c)) {  //blank makes it start again
                    
					state = SCANNER_START;
					
                } else if(isdigit(c)) {  		 // Getting first digit
					
					state = SCANNER_DIGIT;
					strAddChar(word, c);
									
				}
				else if(isalpha(c) || c =='_') { // Getting first letter
				
					state =  SCANNER_WORD;
					strAddChar(word, c);
					
				} else {
					
				switch(c) {
					case TOKEN_EXCLAMATION_MARK: 			// !
						state = SCANNER_EXCLAMATION_MARK; 	// Can be string
						break;
					case TOKEN_QUOTE:						// '
						state = SCANNER_LINE_COMMENT;	    // Make it ignore whole line
						break;
					case TOKEN_SLASH:						// /
						state =  SCANNER_SLASH; 			// can be for dividing or comments
						break;
					case TOKEN_ADD:
						printf("%c = plus\n", c);			// +
						return TOKEN_ADD; 					// Adding
						break;
					case TOKEN_SUB:							// -
						printf("%c = minus\n",c);			// Subtracting
						return TOKEN_SUB;
						break;
					case TOKEN_MUL:							// *
						printf("%c = krát\n",c);
						return TOKEN_MUL; 					// Multiplication
						break;
					case TOKEN_BACKSLASH:					// \\
						state = SCANNER_BACKSLASH; 			// Can be for integer dividing or escape sequence
						break;
					case TOKEN_EQUALS:						// =
						printf("%c = rovná se\n",c);		// Equals
						return TOKEN_EQUALS;
						break;
					case TOKEN_LESS:						// < 
						state = SCANNER_LESS_THAN; 			// Can be less than or less than_or_equal or not equal
						break;
					case TOKEN_MORE:						// >
						state = SCANNER_MORE_THAN; 			// Can be more than or more than_or_equal
						break;
                   	case EOF :
                		return TOKEN_END_OF_FILE;
                	break;
					default:
						return ERROR_LEXICAL; 				// Something else, what is this? Can this happen || not?
					break;
				}	
			}
			
			break;
			case SCANNER_DIGIT:
				if(isdigit(c)) { 					// Getting next digit
					strAddChar(word, c);
					
				} else if(c == '.') { 				// Getting point
					state = SCANNER_FLOAT; 
					strAddChar(word, c);
					
				} else if(c == 'e' || c == 'E') { 	// Getting E or e
					state = SCANNER_EXPONENT_TRY;
					strAddChar(word, c);
					
				} else {
					ungetc(c, file);
					printf("%s = číslo(int)\n", word->str);
					return TOKEN_INTEGER;			// TODO struct	
				}
			break;
			case SCANNER_FLOAT:
				if(isdigit(c)) {
					strAddChar(word, c);
				} else {
					ungetc(c, file);
					printf("%s = číslo(double)\n", word->str);
					return DATA_TYPE_DOUBLE; 		// TODO struct				
				}
			break;
			case SCANNER_EXPONENT_TRY:
				if(c == '+' || c == '-') {  		// Digit is looking like [0-9]+(e|E)(+|-)
					strAddChar(word, c);
					state = SCANNER_EXPONENT;
				} else {
					return ERROR_LEXICAL; 			// Digit is looking like [0-9]+(e|E) and then something bad			
				}
			break;
			case SCANNER_EXPONENT:
				if(isdigit(c)) {
					strAddChar(word, c);
				} else {
					ungetc(c, file);
					printf("%s = číslo(double)\n", word->str);
					return DATA_TYPE_DOUBLE; 		// TODO struct				
				}
			break;
			case SCANNER_EXCLAMATION_MARK:
				if(c == TOKEN_DOUBLE_QUOTE) {  		// " after ! (!")
					state = SCANNER_STRING;
				}
				else{
					return ERROR_LEXICAL; 			// Only ! standing alone			
				}
			break;
			case SCANNER_STRING:
				if(c == TOKEN_DOUBLE_QUOTE) {  		// " after ! (!")
					printf("%s = string\n",word->str);
					return DATA_TYPE_STRING; 		// TODO struct
				} else {
					strAddChar(word, c); 			// Saving next char to word			
				}
			break;
			case SCANNER_WORD:
				if(!(isalnum(c) || c == '_')){ 
                	ungetc(c, file); 				// TODO - not working here, for some reason ungetc(int char, File * stream);
					state = SCANNER_WORD_END;
				} else {
					strAddChar(word, c); 			// Saving next char to word			
				}
			break;
			case SCANNER_WORD_END:
				
				for(int i = 0; i<35; i++) {
					if (strCmpConstStrI(word, reserved[i].word) == 0) {
						printf("%s = reserved (%D) \n", word->str, reserved[i].token);
						return reserved[i].token;
						break;
					}			
				}
				
				return TOKEN_ID;			
			break;
			case SCANNER_SLASH:
				if(c == TOKEN_SLASH) { 
					state = SCANNER_COMMENT; 		// As /'
					printf("starting of commentary\n");
				} else {
					return TOKEN_DIV; 				// Slash used for dividing		
				}
			break;
			case SCANNER_COMMENT:
				if(c == TOKEN_QUOTE) { 
					state = SCANNER_COMMENT_TRY;
				} else {
					state = SCANNER_COMMENT; 		// Still commentary			
				}
			break;
			case SCANNER_COMMENT_TRY:
				if(c == TOKEN_SLASH) { 
					state = SCANNER_START; 			// '/
					printf("ending of comentary\n");
				} else {
					state = SCANNER_COMMENT; 		// There was just ', returning to state of comment		
				}
			break;
			case SCANNER_LESS_THAN:
				if (c == TOKEN_EQUALS) { 
					printf("-> LESS THAN OR EQUAL\n");
					return TOKEN_LESS_OR_EQUAL;
				} else {
					printf("-> LESS THAN\n");
					return TOKEN_LESS; 				// There was just ', returning to state of comment		
				}
			break;
			case SCANNER_MORE_THAN:
				if (c == TOKEN_EQUALS) { 
					printf("-> MORE THAN OR EQUAL\n");
					return TOKEN_MORE_OR_EQUAL;
				} else {
					printf("-> MORE THAN\n");
					return TOKEN_MORE; 				// There was just ', returning to state of comment		
				}
			break;		
		}
	}
return 0;
}
    
  


