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

#include "./library/init.h"

int main() {

    scanner_init("./tests/scanner_test.txt");

	for (int i = 0; i < 22; i++) {

		Token token = scanner_next_token();
		printf("%d  :: %s \n", token.flag, token.ID);
	}

    return 0;
}
