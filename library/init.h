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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#include "utils.h"
#include "str.c"          // Strings - Knihovna pro práci s retezci
#include "tokens.c"       // Definice konstant tokenů
#include "error.c"        // Error   - Knihovna pro odchytávání errorù
#include "instructions.c" // Strings - Knihovna pro práci s instrukcemi
#include "stack.c"        // Stack

#include "files.c"        // Files   - Knihovna pro práci se soubory
#include "tree.c"         // Tree    - Knihovna pro práci s binárním vyhledávacím stromem
#include "tree_debug.c"   //         - Debuger


#include "scanner.c"      // Scanner - Knihovna pro skenování vstupního retezce a vytvareni tokenù
#include "parser.c"       // Scanner - Knihovna pro parsování programu
