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

    //scanner_debug("./tests/Scanner/Test_1.bas");

    parser_init("./tests/Parser/Test_01_Declare_Function.bas");
    parser_run();

    /*
    struct DIM * _return;

    _return = malloc(sizeof(struct DIM));
    getExpression(_return);


    Dump("::: PARSER :: CREATE VAR");

    string val = strChars("3.1415");

    string str0 = strChars("test0");
    struct DIM var0 = createVariable(&str0, &val, DATA_TYPE_INT, FRAME_GLOBAL);
    Dump("%s :: INT :: %i", var0.name.str, var0.valueInteger);

    string str1 = strChars("test1");
    struct DIM var1 = createVariable(&str1, &val, DATA_TYPE_DOUBLE, FRAME_GLOBAL);
    Dump("%s :: DBL :: %f", var1.name.str, var1.valueDouble);


    string str2 = strChars("test2");
    struct DIM var2 = createVariable(&str2, &val, DATA_TYPE_STRING, FRAME_GLOBAL);
    Dump("%s :: STR :: %s", var2.name.str, var2.valueString);
    */
}
