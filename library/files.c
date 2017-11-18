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

    f = fopen (path, "rt");

    if (f == NULL){
       ErrorException(ERROR_INTERN, "Error opening file");
	}

	return f;
}


