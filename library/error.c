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
//	@File				error.c
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////

#include "error.h"

static int __dump_counter = 1;

/*
*	@function ErrorException
*	@param    e      - Error Flag
*	@param    format - Fprint format
*   @param    ...    - Arguments
*/
void ErrorException (int e, char* format, ...) {

    va_list arg;
    va_start(arg, format);


    #ifdef DEBUG
    if (DEBUG) {
        #ifdef DEBUG_LINE
        if (DEBUG_LINE) {
            printf("%3d. ", __dump_counter);
        }
        #endif
        fprintf(stderr, "ERROR (%d) :: ", e);
        va_end(arg);
    }
    #endif
    vfprintf(stderr, format, arg);
    printf("\n");
    va_end(arg);
    if (e) {
       exit(e);
    }
    __dump_counter++;
}


void Dump (char* format, ...) {
    #ifdef DEBUG
    if (DEBUG) {
        va_list arg;
        va_start(arg, format);
        #ifdef DEBUG_TIME
        if (DEBUG_TIME) {
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            printf("%d-%d-%d %d:%d:%d ", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
        }
        #endif
        #ifdef DEBUG_LINE
        if (DEBUG_LINE) {
<<<<<<< HEAD
            printf("%3d. ", __dump_counter++);
=======
            printf("%3d. ", __dump_counter);
>>>>>>> 1c0764e4c9a7c0a361ad8ea954eb1bc3956061a2
        }
        #endif
        printf("DUMP :: ");
        vprintf(format, arg);
        printf("\n");
        va_end(arg);
    }
    #else
        va_list arg;
        va_start(arg, format);
        va_end(arg);
    #endif
    __dump_counter++;
}
