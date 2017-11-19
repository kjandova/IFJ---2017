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

#define DEBUG 1

#include "./library/init.h"

int main() {
    scanner_init("./tests/Test 0.bas");

    Token tok;

	do {
        tok = scanner_next_token();
        const char * nameToken = getTokenName(tok.flag);
		Dump("%d (%s) :: %s", tok.flag, nameToken, tok.ID);
	} while( tok.flag != TOKEN_END_OF_FILE);

    return 0;
}
