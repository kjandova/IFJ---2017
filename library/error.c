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
        fprintf(stderr, "%s (%d) :: ", getErrorName(e), e);

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


/*
*	@function ErrorException
*	@param    e      - Error Flag
*	@param    format - Fprint format
*   @param    ...    - Arguments
*/
void LineErrorException (Token tok, int e, char* format, ...) {

    va_list arg;
    va_start(arg, format);

    printf("%3d. [line:%3d (%3d)] ", __dump_counter, tok.line, tok.position);
    fprintf(stderr, "%s (%d) :: ", getErrorName(e), e);
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
            printf("%3d. ", __dump_counter);
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

void LineDump (Token tok, char* format, ...) {
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
            printf("%3d. [line:%3d (%3d)] ", __dump_counter, tok.line, tok.position);
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

const char * getErrorName(short int e) {
    switch(e) {
        case SUCCESS:        return "SUCCESS";
        case ERROR_LEXICAL:  return "ERROR_LEXICAL";
        case ERROR_SYNTAX:   return "ERROR_SYNTAX";
        case ERROR_DEFINE:   return "ERROR_DEFINE";
        case ERROR_TYPE:     return "ERROR_TYPE";
        case ERROR_CONVERT:  return "ERROR_CONVERT";
        case ERROR_SEMANTIC: return "ERROR_SEMANTIC";
        case ERROR_READ_NUM: return "ERROR_READ_NUM";
        case ERROR_UNINIT:   return "ERROR_UNINIT";
        case ERROR_ZERO_DIV: return "ERROR_ZERO_DIV";
        case ERROR_RUNTIME:  return "ERROR_RUNTIME";
        case ERROR_INTERN:   return "ERROR_INTERN";
    }

    return "ERROR_UNKNOW";
}
