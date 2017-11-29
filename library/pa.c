///////////////////////////////////////////////////////////////////////////////////
//
//	@Project 			IFJ 2017
//
//  @Authors
//  Kristýna Jandová  	xjando04
//  Vilém Faigel		xfaige00
//  Nikola Timková		xtimko01
//  Bc. Václav Dole¸al	xdolez76
//
//  @File				pa.c
//  @Description
//
///////////////////////////////////////////////////////////////////////////////////

#include "str.c"
#include "lltable.c"
#include "stack2.c"


/////////////////////////////////

// ======================================================================
//  PRECEDENCNI SYNTAKTICKA ANALYZA
// =====================================================================

/*
*	@function getToken
*/
int readNextToken = 1;
token * getToken() {
	token *t = tok;

	if (readNextToken) {
    	t = scanner_next_token();
	} else {
		readNextToken = 1;
	}
	
	return t;
}

void tokenPause() {
	readNextToken = 0;
}


/*
*	@function readExpression
*	@param int typeA
*	@param int typeB
*	@description Pretypuje 
*/
int expeRetype(int typeA, int typeB) {
	
	switch (typeA) {
        case DATA_TYPE_INT:
            switch (typeB) {
                case DATA_TYPE_INT:
                	return DATA_TYPE_INT;			
                                			
                case DATA_TYPE_DOUBLE:
                    return DATA_TYPE_DOUBLE;	
			}
		break;
			
		case DATA_TYPE_DOUBLE:
			switch (typeB) {
				case DATA_TYPE_DOUBLE:
					return DATA_TYPE_DOUBLE;	

				case DATA_TYPE_INT:
					return DATA_TYPE_DOUBLE;	
			}
		break;
									
		case DATA_TYPE_STRING: 
			switch (typeB) {
				case DATA_TYPE_STRING:
					return DATA_TYPE_STRING;
			}				
		break;
	}
	
	return 0;
}

