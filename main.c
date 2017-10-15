#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "define.h"
#include "str.h"
#include "scanner.h"


string word;

int main(){
    //int token = 0;
    FILE * f;
    strInit(&word);


        f = fopen ("./test.txt","rt");
        if(f == NULL){
                printf("Error opening file");
                return 99;
	}
	else{
		set_source_file(f);
	}
	printf("posem to funguje\n");
for(int i = 0; i< 22; i++){
	int token = get_next_token(&word);
	printf("%d\n",token);
}
 
    return 0;
}
