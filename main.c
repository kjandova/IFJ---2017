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
//	@File				main.c
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////

#define DEBUG 0

#include "./library/init.h"



int main() {
    Dump("Ahoj");

    scanner_init("./tests/Test 0.bas");

    Token tok;

	do {
        tok = scanner_next_token();
		printf("%d  :: %s \n", tok.flag, tok.ID);
	} while( tok.flag != TOKEN_END_OF_FILE);

    return 0;
}
