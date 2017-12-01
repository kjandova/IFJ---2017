///////////////////////////////////////////////////////////////////////////////////
//
//	@Project 			IFJ 2017
//
//  @Authors
//  Kristýna Jandová  	xjando04
//  Vilém Faigel		xfaige00
//  Nikola Timková		xtimko01
//  Bc. Václav Doležal	xdolez76
//
//  @File				stack2.h
//  @Description
//
///////////////////////////////////////////////////////////////////////////////////



#ifndef IFJ_TREE_H
#define IFJ_TREE_H


struct stack {
	int members;
	void *arr[32];
	struct stack *next;
};

typedef struct stack * stack_t;


void stack_push(stack_t *s, void *item);
int stack_pop(stack_t *s, void **result);
int stack_peek(stack_t *s, void **result);
void stack_clean(stack_t *s);

#endif
