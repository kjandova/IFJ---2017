///////////////////////////////////////////////////////////////////////////////////
//
//	@Project 			IFJ 2017
//
//  @Authors
//  Krist�na Jandov�  	xjando04
//  Vil�m Faigel		xfaige00
//  Nikola Timkov�		xtimko01
//	Bc. V�clav Dole�al	xdolez76
//
//	@File				files.c
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////

#include "files.h"

FILE * loadFile(char * path) {

    FILE * f;

    if  (path) {
        f = fopen (path, "rt");
    } else {
        f = stdin;
    }

    if (f == NULL){
       ErrorException(ERROR_INTERN, "Error opening stream file");
	}

	return f;
}

FILE * writeFile(char * path) {

    FILE * f;

    if  (path) {
        f = fopen (path, "w+");
    } else {
        f = stdout;
    }

    if (f == NULL){
       ErrorException(ERROR_INTERN, "Error opening stream file");
	}

	return f;
}

