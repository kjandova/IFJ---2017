#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "define.h"
#include "str.h"

FILE * file;

void set_source_file(FILE *f){
    file = f;
}

int get_next_token(string *word){
	
	char *reserved[35]={ "AS","ASC","DECLARE","DIM","DO","DOUBLE","ELSE","END","CHR","FUNCTION","IF","INPUT","INTEGER","LENGTH","LOOP","PRINT","RETURN","SCOPE","STRING","SUBSTR","THEN","WHILE","AND","BOOLEAN","CONTINUE","ELSEIF","EXIT","FALSE","FOR","NEXT","NOT","OR","SHARED","STATIC","TRUE"};
	char tok[50] = "TOKEN_";	
	char c;
	strClear(word);
	int state = START;	//because start
	while(1){
	c = getc(file);
		switch(state){
			case START: //every new statement 
				if(isspace(c)){  //blank makes it start again
                    			state = START;
					
                		}
				else if(isdigit(c)){  //getting first digit
					state = DIGIT;
					strAddChar(word, c);
									
				}
				else if(isalpha(c) || c =='_'){  //getting first letter
					state = WORD;
					strAddChar(word, c);
					
				}
				else{
				switch(c){
					case '!':
						state = EXCLAMATION_MARK; //can be string
						break;
					case '\'':
						state = LINE_COMMENT; //make it ignore whole line
						break;
					case '/':
						state = SLASH; //can be for dividing or comments
						break;
					case '+':
						printf("%c = plus\n",c);
						return TOKEN_ADD; //adding

						break;
					case '-':
						printf("%c = minus\n",c);
						return TOKEN_SUB; //subtracting
						break;
					case '*':
						printf("%c = krát\n",c);
						return TOKEN_MUL; //multiplication
						break;
					case 92:
						state = BACKSLASH; // can be for integer dividing or escape sequence
						break;
					case '=':
						printf("%c = rovná se\n",c);
						return TOKEN_EQUALS;	//equals
						break;
					case '<':
						state = LESS_THAN; //can be less than or less than_or_equal or not equal
						break;
					case '>':
						state = MORE_THAN; // can be more than or more than_or_equal
						break;
                   		        case EOF :
                		                return TOKEN_END_OF_FILE;
                	 	                break;
					default:
						return LEXICAL_ERROR; //something else, what is this? Can this happen || not?
				break;
				}	
				}
			break;
			case DIGIT:
				if(isdigit(c)){ //getting next digit
					strAddChar(word, c);
				}
				else if(c == '.'){ //getting point
					state = FLOAT; 
					strAddChar(word, c);
				}
				else if(c == 'e' || c == 'E'){ //getting E or e
					state = EXPONENT_TRY;
					strAddChar(word, c);
				}
				else{
					ungetc(c, file);
					printf("%s = číslo(int)\n",word->str);
					return TOKEN_INT; //TODO struct	
			
				}
			break;
			case FLOAT:
				if(isdigit(c)){
					strAddChar(word, c);
				}
				else{
					ungetc(c, file);
					printf("%s = číslo(double)\n",word->str);
					return TOKEN_DOUBLE_N; //TODO struct				
				}
			break;
			case EXPONENT_TRY:
				if(c == '+' || c == '-'){  //digit is looking like [0-9]+(e|E)(+|-)
					strAddChar(word, c);
					state = EXPONENT;
				}
				else{
					return LEXICAL_ERROR; //digit is looking like [0-9]+(e|E) and then something bad			
				}
			break;
			case EXPONENT:
				if(isdigit(c)){
					strAddChar(word, c);
				}
				else{
					ungetc(c, file);
					printf("%s = číslo(double)\n",word->str);
					return TOKEN_DOUBLE_N; //TODO struct				
				}
			break;
			case EXCLAMATION_MARK:
				if(c == '\"'){  // " after ! (!")
					state = STRING;
				}
				else{
					return LEXICAL_ERROR; //only ! standing alone			
				}
			break;
			case STRING:
				if(c == '\"'){  // " after ! (!")
					printf("%s = string\n",word->str);
					return TOKEN_STRING_N; //TODO struct
				}
				else{
					strAddChar(word, c); //saving next char to word			
				}
			break;
			case WORD:
				if(!(isalnum(c) || c == '_')){ 
                  		        ungetc(c, file); //TODO - not working here, for some reason ungetc(int char, File * stream);
					state = WORD_END;
				}
				else{
					strAddChar(word, c); //saving next char to word			
				}
			break;
			case WORD_END:
				for(int i = 0; i<35;i++){
					if(strCmpConstStrI(word,reserved[i])==0){
						strcat(tok,reserved[i]);
						printf("%s = reserved\n",word->str);
						return 0;
						break;
					}			

				}
				if(strcmp(tok,"TOKEN_")==0){
					strcat(tok,"ID");
					printf("%s = ID\n",word->str);
					return TOKEN_ID; //TODO struct 
				}	
				
				
			break;
			case SLASH:
				if(c == '\''){ 
					state = COMMENT; // as /'
					printf("starting of commentary\n");
				}
				else{
					return TOKEN_DIV; // slash used for dividing		
				}
			break;
			case COMMENT:
				if(c == '\''){ 
					state = COMMENT_TRY;
				}
				else{
					state = COMMENT; //still commentary			
				}
			break;
			case COMMENT_TRY:
				if(c == '/'){ 
					state = START; // '/
					printf("ending of comentary\n");
				}
				else{
				state = COMMENT; // there was just ', returning to state of comment		
				}
			break;
			case LESS_THAN:
				if(c == '='){ 
					printf("-> LESS THAN OR EQUAL\n");
					return TOKEN_LESS_THAN_OR_EQUAL;
				}
				else{
					printf("-> LESS THAN\n");
					return TOKEN_LESS_THAN; // there was just ', returning to state of comment		
				}
			break;
			case MORE_THAN:
				if(c == '='){ 
					printf("-> MORE THAN OR EQUAL\n");
					return TOKEN_MORE_THAN_OR_EQUAL;
				}
				else{
					printf("-> MORE THAN\n");
					return TOKEN_MORE_THAN; // there was just ', returning to state of comment		
				}
			break;



				
		}

	}
return 0;
}
    
  


