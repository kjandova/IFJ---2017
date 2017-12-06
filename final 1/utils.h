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
