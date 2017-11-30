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
unsigned int getTableIndex(int flag) {
	switch(flag) {
		case TOKEN_ADD: 					return 0;	// +
		case TOKEN_SUB: 					return 1;	// -
		case TOKEN_MUL: 					return 2;	// *
		case TOKEN_DIV:		 				return 3;	// /
		case TOKEN_BACKSLASH:				return 4;	// '\' Celociselne deleni
		case TOKEN_MORE:			 		return 5;	// >
		case TOKEN_LESS:	 				return 6;	// <
		case TOKEN_MORE_OR_EQUAL: 			return 7;	// >=
		case TOKEN_LESS_OR_EQUAL:			return 8;	// <=
		case TOKEN_EQUALS:	 				return 9;	// =
		case TOKEN_NON_EQUAL:	 			return 10;	// <>
		case TOKEN_BRACKET_LEFT:			return 11;	// (
		case TOKEN_BRACKET_RIGHT: 			return 12;	// )
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
