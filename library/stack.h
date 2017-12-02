///////////////////////////////////////////////////////////////////////////////////////////////////
//
//	IFH 2017
//	stack.h
//
//	citate: [Online: http://pseudomuto.com/development/2013/06/19/implementing-a-generic-stack-in-c/
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __STACK_H
#define __STACK_H

// from previous post on linked-list implementation
// in C
#include "list.h"
 
typedef struct {
  list *list;
} stack;
 
void stack_new(stack *s, int elementSize);
void stack_destroy(stack *s);
void stack_push(stack *s, void *element);
void stack_pop(stack *s, void *element);
void stack_peek(stack *s, void *element);
int stack_size(stack *s);

#endif