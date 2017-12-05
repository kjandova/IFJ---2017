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
//	@File				init.h
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////

#ifndef IFJ_INIT_H
#define IFJ_INIT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h>
#include <unistd.h>

// HEADERS
#include "utils.h"
#include "str.h"
#include "tokens.h"
#include "error.h"
#include "list.h"
#include "stack.h"
#include "instructions.h"


// LIBRARY

#include "tokens.c"       // Definice konstant tokenů


#include "error.c"        // Error   - Knihovna pro odchytávání errorù
#include "str.c"          // Strings - Knihovna pro práci s retezci
#include "list.c"         // List    - Knihovna pro práci s datovými poly
#include "stack.c"        // Stack   - Knihovna pro práci se stackem
#include "instructions.c" // Strings - Knihovna pro práci s instrukcemi


#include "files.c"        // Files   - Knihovna pro práci se soubory
#include "tree.c"         // Tree    - Knihovna pro práci s binárním vyhledávacím stromem
#include "tree_debug.c"   //         - Debuger


#include "scanner.c"      // Scanner - Knihovna pro skenování vstupního retezce a vytvareni tokenù
#include "parser.c"       // Scanner - Knihovna pro parsování programu

//#include "tests.c"

#endif // IFJ_INIT_H


struct globalArgs_T {
    int   help;
    char *filePathInput;
    char *filePathOutput;
    int   dumpEnable;
    char *fileDumpOutput;
} globalArgs;


void help() {
    printf("PROJEKT IFJ 2017");
}

void init(int argc, char ** argv) {
    int opt;
    globalArgs.dumpEnable = DEBUG_DISABLE;

    //$IFJ [-h][-f <path>][-o [<path>]][-d [<path>][-i]

    while ((opt = getopt (argc, argv, "hf:o:d::i")) != -1) {
        switch (opt) {
            case 'h': /* -h option - Help */
                help();
            break;
            case 'f': /* -f option - Input File Path  | NULL -> stdin */
                globalArgs.filePathInput   = optarg;
            break;
            case 'o': /* -o option - Output File Path | NULL -> stdout */
                globalArgs.filePathOutput  = optarg;
            break;
            case 'd': /* -d option - DUMP Output File Path  | NULL -> stdout */
                globalArgs.fileDumpOutput  = optarg;
                globalArgs.dumpEnable      = DEBUG_ENABLE;
            break;
            case 'i': /* -i option - DUMP More info */
                globalArgs.dumpEnable     |= DEBUG_LINE;
            break;
        }
    }

    ErrorInit( writeFile(globalArgs.fileDumpOutput),  writeFile(globalArgs.fileDumpOutput), globalArgs.dumpEnable );
}
