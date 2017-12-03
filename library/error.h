///////////////////////////////////////////////////////////////////////////////////
//
//	@Project 			IFJ 2017
//
//  @Authors
//  Kristýna Jandová  	xjando04
//  Vilém Faigel		xfaige00
//  Nikola Timková		xtimko01
//	Bc. Václav Doležal	xdolez76
//
//	@File				error.h
//	@Description
//
//
///////////////////////////////////////////////////////////////////////////////////

#ifndef IFJ_ERROR_H
#define IFJ_ERROR_H

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "tokens.h"
//
// ERROR CODE
//

enum Errors {
	SUCCESS	= 0,   		// Bez chyb
	ERROR_LEXICAL,  	// Lexikalni chyba
	ERROR_SYNTAX,   	// Syntakticka chyba
	ERROR_DEFINE,   	// Nedefinovana fce/prom, redefinace fce/prom
	ERROR_TYPE,     	// Typova nekompatibilita operace, spatny pocet param
	ERROR_CONVERT,  	// Chyba odvozovani datoveho typu
	ERROR_SEMANTIC, 	// Ostatni semanticke chyby
	ERROR_READ_NUM, 	// Chyba pri cteni cisla ze vstupu
	ERROR_UNINIT,   	// Prace s neinicializovanou prom
	ERROR_ZERO_DIV, 	// Deleni nuou
	ERROR_RUNTIME,      // Ostatni behove chyby
	ERROR_INTERN  =	99  // Interni chyba interpretu
};

void ErrorException     (int e, char* format, ...);
void LineErrorException (Token tok, int e, char* format, ...);
void Dump (char* format, ...);
void LineDump (Token tok, char* format, ...);
const char * getErrorName(short int e);

#endif // IFJ_ERROR_H
