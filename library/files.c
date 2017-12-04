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
       ErrorException(ERROR_INTERN, "Error opening file");
	}

	return f;
}



