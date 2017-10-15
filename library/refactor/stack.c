#include "stack.h"


/*
*  @function SPrint
* @parm tStack *S
* @description vypíše bsah stacku
*/ 
void SPrint(tStack *S) {
    printf("\n<< STACK PRINT >>\n");
    for(int i = 1; i <= (*S)->top;i++) {
        printf("ITEM type::%i\n", (*S)->item[i].type);
    }
    printf("<< ----------- >>\n\n");
}


/*
* 	@function SInit
*	@parm tStack *S
*	@description  Inicializace zasobniku
*/ 
int SInit(tStack *S) {
	//printf("STACK INIT\n");

	if (!((*S) = malloc(sizeof(struct tStacke)))) {
    	return E_FILE;
	}
  	
	if (!((*S)->item = malloc(MAXSTACK * sizeof(struct iStack)))) {
    	return E_FILE;
  	}
 
    (*S)->top 	= 0;
    (*S)->size 	= MAXSTACK;
 
  	for(int i = 0; i < MAXSTACK; i++) {
        (*S)->item[i].type	= 0;
        (*S)->item[i].data	= NULL;
  	}

  //printf("STACK INIT OK\n");	
	return 0;
}


/*
* 	@function SDispose
*	@parm tStack *S
*	@description  Zruseni zasobniku
*/ 
void SDispose(tStack *S) {
	//printf("STACK DISPONSE\n");
    //for(int i = (*S)->size-1; i > 0; i--)
    //	free((*S)->item);
  free(*S);
}


/*
* 	@function SPush
*	@parm tStack *S
*	@parm int type
*	@parm tabItem *item
*	@description Vlozit hodnotu na vrchol zasobniku
*/ 
void SPush(tStack *S, int type, tabItem *item) {

	//printf("STACK PUSH\n");
  	if ((*S)->top >= (*S)->size) {
  		
      	(*S)->size += MAXSTACK;
     	 	(*S)->item = realloc (
  			(*S)->item, 
  			(*S)->size * sizeof (struct tStacke)
  		);
   	 	
  	}
  
  	(*S)->top++;
  	
  	(*S)->item[(*S)->top].type	= type;
  	(*S)->item[(*S)->top].data	= item;


    ///////////////////////////
    //////////////////////////
    //SPrint(S);
}


/*
* 	@function SPush_term
*	@parm tStack *S
*	@parm int ptr
*	@parm tData *addr
*	@description 
*/ 
void SPush_term(tStack *S, int ptr, int addr) {
	//printf("STACK PUSH TERM\n");
  
  int type;
  	
	tabItem *data;
	
	int sTop = (*S)->top = ++addr;
	

  if (sTop >= (*S)->size) {
  		
   	(*S)->size += MAXSTACK;
    (*S)->item = realloc (
  		(*S)->item,
  		(*S)->size * sizeof (struct tStacke)
    );
  }
  
  data 	= (*S)->item[sTop].data;
  type	= (*S)->item[sTop].type;
 
  (*S)->item[sTop].data = NULL;
 	(*S)->item[sTop].type = ptr;
 
 	if (type == PA_E) {
  		
  	sTop = (*S)->top = ++addr;
    	
   	if (sTop >= (*S)->size) {
   		(*S)->size += MAXSTACK;
   		(*S)->item = realloc(
 		  	(*S)->item, 
 				(*S)->size * sizeof (struct tStacke)
 			);
   	}
    	
		(*S)->item[sTop].data = data;
    (*S)->item[sTop].type = type;
  }

  ///////////////////////////
  //////////////////////////
  //SPrint(S);
}
 
 
 
/*
* 	@function SPop
*	@parm tStack *S
*	@description Zrusi prvek na vrcholu zasobniku
*/ 
void SPop(tStack *S) {
  //printf("STACK POP\n");
	if ((*S)->top > 0) {
    	(*S)->item[(*S)->top].type = 0;
    	(*S)->top--;
	}

  ///////////////////////////
    //////////////////////////
    //SPrint(S);
}
 
 
/*
* 	@function STop
*	@parm tStack *S
*	@description Obsah vrcholu zasobniku
*/ 
tStack_item STop(tStack *S) {
	//printf("STACK TOP\n");

	if ((*S)->top == 0) {
    	fprintf(stderr,"chyba zasobniku");
  	}
  	
	return (*S)->item[(*S)->top];
}


/*
* 	@function SFind_Term
*	@parm tStack *S
*	@description Najde pozici terminalu na zasobniku
*/ 
int SFind_Term(tStack * S) {
	//printf("STACK FIND TERM\n");
  int type = (*S)->item[(*S)->top].type;

  if (isOperations(type) || type == PA_ID || type == PA_LT) {
    return (*S)->top;
  }
  	
	return (*S)->top-1;
}
 

/*
* 	@function STop_Term
*	@parm tStack *S
*	@description Najde pozici terminalu na zasobniku a zjisti jeho informace
*/ 
tStack_item STop_Term(tStack *S) {
  

  tStack_item term;
  term = (*S)->item[SFind_Term(S)];

  //printf("STACK TOP TERM Type::%i \n", term.type);
  return term;
}

