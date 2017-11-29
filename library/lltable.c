#include "lltable.h"

/*
*	LL TABLE
*/

int PATable [15][15] = {  
/*             +        -         *         /          \         >         <        >=        <=         =        <>          (         )          i           $       */
/*  +  */ {PA_GREAT, PA_GREAT, PA_LESS,  PA_LESS,  PA_LESS,  PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_LESS, 	PA_GREAT,   PA_LESS,    PA_GREAT,},
/*  -  */ {PA_GREAT, PA_GREAT, PA_LESS,  PA_LESS,  PA_LESS,  PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_LESS, 	PA_GREAT,   PA_LESS,    PA_GREAT,},
/*  *  */ {PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_LESS, 	PA_GREAT,   PA_LESS,    PA_GREAT,},
/*  /  */ {PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_LESS, 	PA_GREAT,   PA_LESS,    PA_GREAT,},
/*  \  */ {PA_GREAT, PA_GREAT, PA_LESS,  PA_LESS,  PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_LESS,  PA_LESS, 	PA_GREAT,   PA_LESS,    PA_GREAT,},
/*  >  */ {PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_ERROR, PA_ERROR, PA_ERROR, PA_ERROR, PA_ERROR, PA_ERROR, PA_LESS, 	PA_GREAT,   PA_LESS,    PA_GREAT,},
/*  <  */ {PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_ERROR, PA_ERROR, PA_ERROR, PA_ERROR, PA_ERROR, PA_ERROR, PA_LESS, 	PA_GREAT,   PA_LESS,    PA_GREAT,},
/*  >= */ {PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_ERROR, PA_ERROR, PA_ERROR, PA_ERROR, PA_ERROR, PA_ERROR, PA_LESS, 	PA_GREAT,   PA_LESS,    PA_GREAT,},
/*  <= */ {PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_ERROR, PA_ERROR, PA_ERROR, PA_ERROR, PA_ERROR, PA_ERROR, PA_LESS, 	PA_GREAT,   PA_LESS,    PA_GREAT,},
/*  =  */ {PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_ERROR, PA_ERROR, PA_ERROR, PA_ERROR, PA_ERROR, PA_ERROR, PA_LESS, 	PA_GREAT,   PA_LESS,    PA_GREAT,},
/*  <> */ {PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_ERROR, PA_ERROR, PA_ERROR, PA_ERROR, PA_ERROR, PA_ERROR, PA_LESS, 	PA_GREAT,   PA_LESS,    PA_GREAT,},
/*  (  */ {PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS, 	PA_ASSIG,   PA_LESS,    PA_ERROR,},
/*  )  */ {PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_ERROR, 	PA_GREAT,   PA_ERROR,   PA_GREAT,},
/*  i  */ {PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_GREAT, PA_ERROR, 	PA_GREAT,   PA_ERROR,   PA_GREAT,},
/*  $  */ {PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS,  PA_LESS, 	PA_ERROR,   PA_LESS,    PA_ERROR,},
};


/* 
*	@function getTableIndex
*	@param i
*	@description Kontrola indexovani tabulky
*/
unsigned int getTableIndex(int i) {
	switch(i) {
		case TOKEN_ADD: 					return 0;	// +
		case TOKEN_SUB: 					return 1;	// -
		case TOKEN_MUL: 					return 2;	// *
		case TOKEN_DIV:		 				return 3;	// /
		case TOKEN_DIV_B:	 				return 4;	// \.  
		case TOKEN_MORE:			 		return 5;	// >
		case TOKEN_LESS:	 				return 6;	// <
		case TOKEN_MORE_OR_EQUAL: 			return 7;	// >=
		case TOKEN_LESS_OR_EQUAL:			return 8;	// <=
		case TOKEN_EQUALS:	 				return 9;	// =
		case TOKEN_NON_EQUAL:	 			return 10;	// <>
		case TOKEN_BRACKET_RIGHT:			return 11;	// (
		case TOKEN_BRACKET_LEFT: 			return 12;	// )
		case PA_ID:							return 13;  // i
		case PA_LT:							return 14;  // $
	}
  return ERR_INSIDE;
}
 
 
/* 
*	@function getTable
*	@param i
*	@param j
*	@description Najití hodnot v tabulce
*/
unsigned int getTable(int i, int j) {
	return PATable[getTableIndex(i)][getTableIndex(j)];
}


int isOperations(int type) {
	switch(type) {
		//ARYTHMETIC
		case TOKEN_ADD:			// +
		case TOKEN_SUB:			// -
		case TOKEN_MUL:			// *
		case TOKEN_DIV:			// /
		case TOKEN_DIV_B:		// \.  
		// COMPARISON
		case TOKEN_LESS: 			// <
		case TOKEN_MORE:			// >
		case TOKEN_LESS_OR_EQUAL:	// <=
		case TOKEN_MORE_OR_EQUAL:	// >=
		case TOKEN_EQUALS:			// =
		case TOKEN_NON_EQUAL:		// <>
			return 1;
	}

	return 0;
}


int isID(int type) {
	switch(type) {
		case DATA_TYPE_INT:		
		case DATA_TYPE_DOUBLE:	
		case DATA_TYPE_STRING:	
		case TOKEN_ID:	
		return PA_ID;
	}

	if (isOperations(type)) return type;
	
	return PA_LT;
}