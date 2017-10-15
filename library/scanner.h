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


typedef struct {
	int   token;
	char *value;
} Token;

void set_source_file(FILE *f);
int get_next_token(string *word);

