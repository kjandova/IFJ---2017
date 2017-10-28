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
//  @File				stack2.c
//  @Description
//
///////////////////////////////////////////////////////////////////////////////////


#include <stdlib.h>
#include <err.h>

#include "stack2.h"
#include "define.h"

#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))

struct stack2 {
	int members;
	void *arr[32];
	struct stack2 *next;
};

static void stack_extend(struct stack2 **stack)
{
	struct stack2 *tmp;
	tmp = calloc(1, sizeof(*tmp));
	if (!tmp)
		err(RUNTIME_ERROR, "runtime error");
	tmp->next = *stack;
	*stack = tmp;
}

void stack_push(struct stack2 **stack, void *item)
{
	if (!*stack || (*stack)->members >= ARRAY_SIZE((*stack)->arr))
		stack_extend(stack);

	(*stack)->arr[(*stack)->members] = item;
	(*stack)->members++;
}

static void stack_reduce(struct stack2 **stack)
{
	struct stack2 *tmp = *stack;
	*stack = tmp->next;
	free(tmp);
}

int stack_pop(struct stack2 **stack, void **result)
{
	if (!stack_peek(stack, result))
		return 0;

	(*stack)->members--;
	if (!(*stack)->members && (*stack)->next)
		stack_reduce(stack);
	return 1;
}

int stack_peek(struct stack2 **stack, void **result)
{
	int index;
	if (!(*stack) || !(*stack)->members) {
		return 0;
	}

	index = (*stack)->members -1;
	if (result)
		*result = (*stack)->arr[index];
	return 1;
}

void stack_clean(struct stack2 **stack)
{
	while (*stack)
		stack_reduce(stack);
}
