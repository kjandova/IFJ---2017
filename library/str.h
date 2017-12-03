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
//	@File				str.h
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////

#ifndef IFJ_STR_H
#define IFJ_STR_H

#include <malloc.h>
#include <string.h>
#include <strings.h>


// konstanta STR_LEN_INC udava, na kolik bytu provedeme pocatecni alokaci pameti
// pokud nacitame retezec znak po znaku, pamet se postupne bude alkokovat na
// nasobky tohoto cisla

#define STR_LEN_INC 8
#define STR_ERROR   1
#define STR_SUCCESS 0


typedef struct {
   char* str;        // misto pro dany retezec ukonceny znakem '\0'
   int length;       // skutecna delka retezce
   int allocSize;    // velikost alokovane pameti
} string;


int  strInit(string *s);
void strFree(string *s);

void strClear(string *s);
int  strAddChar(string *s1, char c);
int  strCopyString(string *s1, string *s2);
int  strCmpString(string *s1, string *s2);
int  strCmpConstStr(string *s1, char *s2);
int  strCmpConstStrI(string *s1, char* s2);

char *strGetStr(string *s);
int  strGetLength(string *s);


#endif // IFJ_STR_H
