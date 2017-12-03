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

#define DEBUG      1
#define DEBUG_LINE 1
//#define DEBUG_TIME 1

#include "./library/init.h"

int main() {

    scanner_debug("./tests/Scanner/Test_01_Tokens.txt");

    //parser_init("./tests/Parser/Test_01_Declare_Function.bas");
    //parser_run();

    tests_run("./tests");

    return 0;
}
