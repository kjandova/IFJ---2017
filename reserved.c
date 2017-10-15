#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int main () {


char *reserved[35]={ "AS","ASC","DECLARE","DIM","DO","DOUBLE","ELSE","END","CHR","FUNCTION","IF","INPUT","INTEGER","LENGTH","LOOP","PRINT","RETURN","SCOPE","STRING","SUBSTR","THEN","WHILE","AND","BOOLEAN","CONTINUE",
"ELSEIF","EXIT","FALSE","FOR","NEXT","NOT","OR","SHARED","STATIC","TRUE"};
char tok[50] = "TOKEN_";
char word[20];

printf("zadej slovo: ");
scanf ("%s", word);

printf("zadáno: %s\n",word);
int k = 200;
for(int i = 0; i<35;i++){

	printf("#define %s%s %d\n",tok,reserved[i],k);
	/*if(strcasecmp(word,reserved[i])==0){
		strcat(tok,reserved[i]);
		break;			
	}*/
	k++;
}
if(strcmp(tok,"TOKEN_")==0){
	strcat(tok,"ID");
}
printf("Výsledek: %s\n",tok);





return 0;
}
