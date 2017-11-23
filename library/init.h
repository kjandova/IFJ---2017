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

#include "tokens.c"		// Definice konstant tokenů
#include "error.c"      // Error   - Knihovna pro odchytávání errorù
#include "files.c"      // Files   - Knihovna pro práci se soubory
#include "tree.c"       // Tree    - Knihovna pro práci s binárním vyhledávacím stromem
#include "tree_debug.c" // Tree Debuger
#include "str.c"		// Strings - Knihovna pro práci s øetìzci
#include "scanner.c"	// Scanner - Knihovna pro skenování vstupního øetìzce a vytváøení tokenù
