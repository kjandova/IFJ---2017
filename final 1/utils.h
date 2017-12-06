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
//	@File				utils.h
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////

#ifndef IFJ_UTILS_H
#define IFJ_UTILS_H

#define unused(x) (void)(x)
#define NEW(var) \
	((var) = malloc(sizeof(*(var))))

#define NEWC(c, var) \
	((var) = calloc((c), sizeof(*(var))))

#define DEL(var) \
	do { \
		free(var); \
		var = NULL; \
	} while (0)

#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))

#endif // IFJ_UTILS_H
