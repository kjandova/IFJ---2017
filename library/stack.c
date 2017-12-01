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

#include "stack.h"

struct stack {
	int members;
	void *arr[32];
	struct stack *next;
};


//

static void stack_extend(struct stack **s)
{
	struct stack *tmp;
	tmp = calloc(1, sizeof(*tmp));
	if (!tmp)
		ErrorException(ERROR_RUNTIME, "STACK :: Calloc");
	tmp->next = *s;
	*s = tmp;
}

void stack_push(struct stack **s, void *item)
{
	if (!*s || (*s)->members >= ARRAY_SIZE((*s)->arr))
		stack_extend(s);

	(*s)->arr[(*s)->members] = item;
	(*s)->members++;
}

static void stack_reduce(struct stack **s)
{
	struct stack2 *tmp = *s;
	*s = tmp->next;
	free(tmp);
}

int stack_pop(struct stack **s, void **result)
{
	if (!stack_peek(s, result))
		return 0;

	(*s)->members--;
	if (!(*s)->members && (*s)->next)
		stack_reduce(s);
	return 1;
}

int stack_peek(struct s **s, void **result)
{
	int index;
	if (!(*s) || !(*s)->members) {
		return 0;
	}

	index = (*s)->members -1;
	if (result)
		*result = (*s)->arr[index];
	return 1;
}

int stack_index(struct stack **s, int index, void **result)
{
	if (index >= (*s)->members)
		return 0;

	*result = (*s)->arr[index];

	return 1;
}

void stack_clean(struct stack **s)
{
	while (*s)
		stack_reduce(s);
}
