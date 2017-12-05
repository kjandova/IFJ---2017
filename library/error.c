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

#define DEBUG_DISABLE  0
#define DEBUG_ENABLE   1
#define DEBUG_LINE     2
#define DEBUG_TIME     4

struct __ErrorInit_T {
    int    debugEnabled;
    FILE * outputError;
    FILE * outputDump;
} __ErrorInit;


/*
*	@function ErrorException
*	@param    e      - Error Flag
*	@param    format - Fprint format
*   @param    ...    - Arguments
*/
void ErrorInit(FILE * dump, FILE * error, int debugEnabled) {

    __ErrorInit.outputDump       = (dump == NULL)  ? stdout:dump;
    __ErrorInit.outputError      = (error == NULL) ? stdout:error;
    __ErrorInit.debugEnabled     = (debugEnabled)  ? debugEnabled : DEBUG_DISABLE;

}

void DebugConfigure(int debugEnabled) {
    __ErrorInit.debugEnabled     = (debugEnabled)  ? debugEnabled : DEBUG_DISABLE;

}

/*
*	@function ErrorException
*	@param    e      - Error Flag
*	@param    format - Fprint format
*   @param    ...    - Arguments
*/
void ErrorException (int e, char* format, ...) {

    va_list arg;
    va_start(arg, format);

    if (__ErrorInit.debugEnabled) {
        if (__ErrorInit.debugEnabled & DEBUG_LINE) {
            fprintf(__ErrorInit.outputError, "%3d. ", __dump_counter);
        }
        fprintf(__ErrorInit.outputError, "%s (%d) :: ", getErrorName(e), e);
    }

    vfprintf(__ErrorInit.outputError, format, arg);
    fprintf(__ErrorInit.outputError, "\n");
    va_end(arg);

    if (e) {
       exit(e);
    }
    __dump_counter++;
}


/*
*	@function LineErrorException
*	@param    tok    - Token
*	@param    e      - Error Flag
*	@param    format - Fprint format
*   @param    ...    - Arguments
*/
void LineErrorException (Token tok, int e, char* format, ...) {

    va_list arg;
    va_start(arg, format);

    fprintf(__ErrorInit.outputError, "%3d. [line:%3d (%3d)] ", __dump_counter, tok.line, tok.position);
    fprintf(__ErrorInit.outputError, "%s (%d) :: ", getErrorName(e), e);
    vfprintf(__ErrorInit.outputError, format, arg);
    fprintf(__ErrorInit.outputError, "\n");
    va_end(arg);

    if (e) {
       exit(e);
    }

    __dump_counter++;
}

/*
*	@function Dump
*	@param    format - fprint format
*   @param    ...    - Arguments
*/
void Dump (char* format, ...) {
    if (__ErrorInit.debugEnabled) {

        va_list arg;
        va_start(arg, format);

        if (__ErrorInit.debugEnabled & DEBUG_LINE) {
            fprintf(__ErrorInit.outputDump, "%3d. ", __dump_counter);
        }

        if (__ErrorInit.debugEnabled & DEBUG_TIME) {
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            fprintf(__ErrorInit.outputDump, "%d-%d-%d %d:%d:%d ", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
        }

        fprintf(__ErrorInit.outputDump, "DUMP :: ");
        vfprintf(__ErrorInit.outputDump, format, arg);
        fprintf(__ErrorInit.outputDump, "\n");
        va_end(arg);

        __dump_counter++;
    }
}

void LineDump (Token tok, char* format, ...) {

    if (__ErrorInit.debugEnabled) {

        va_list arg;
        va_start(arg, format);

        if (__ErrorInit.debugEnabled & DEBUG_LINE) {
            fprintf(__ErrorInit.outputDump, "%3d. ", __dump_counter);
        }

        if (__ErrorInit.debugEnabled & DEBUG_TIME) {
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            fprintf(__ErrorInit.outputDump, "%d-%d-%d %d:%d:%d ", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
        }

        if (__ErrorInit.debugEnabled & DEBUG_LINE) {
            fprintf(__ErrorInit.outputDump, "[line:%3d (%3d)] ", tok.line, tok.position);
        }

        fprintf(__ErrorInit.outputDump, "DUMP :: ");
        vfprintf(__ErrorInit.outputDump, format, arg);
        fprintf(__ErrorInit.outputDump,"\n");
        va_end(arg);

        __dump_counter++;
    }
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
