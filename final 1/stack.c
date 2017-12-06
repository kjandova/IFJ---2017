///////////////////////////////////////////////////////////////////////////////////////////////////
//
//	IFH 2017
//	stack.c
//
//	citate: [Online: http://pseudomuto.com/development/2013/06/19/implementing-a-generic-stack-in-c/
//
///////////////////////////////////////////////////////////////////////////////////////////////////



#include "stack.h"


/*
*  @function list_new
*  @param    list *list
*  @param    int elementSize
*  @param    freeFunction freeFn
*/
void stack_new(stack *s, int elementSize) {
  s->list = malloc(sizeof(list));
  // make sure the malloc call didn't fail...
  assert(s->list != NULL);

  list_new(s->list, elementSize);
}


/*
*  @function list_new
*  @param    stack *s
*/
void stack_destroy(stack *s) {
  list_destroy(s->list);
  free(s->list);
}


/*
*  @function stack_push
*  @param    stack *s
*  @param    void *element
*/
void stack_push(stack *s, void *element) {
  list_prepend(s->list, element);
}


/*
*  @function stack_pop
*  @param    stack *s
*  @param    void *element
*/
void stack_pop(stack *s, void *element) {
  // don't pop an empty stack!
  assert(stack_size(s) > 0);

  list_head(s->list, element, true);
}


/*
*  @function stack_peek
*  @param    stack *s
*  @param    void *element
*/
void stack_peek(stack *s, void *element) {
  assert(stack_size(s) > 0);
  list_head(s->list, element, false);
}


/*
*  @function stack_size
*  @param    stack *s
*/
int stack_size(stack *s) {
  return list_size(s->list);
}
