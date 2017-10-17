#ifndef IFJ_TREE_H
#define IFJ_TREE_H

typedef struct stack2 * stack_t;

void stack_push(stack_t *stack, void *item);
int stack_pop(stack_t *stack, void **result);
int stack_peek(stack_t *stack, void **result);
void stack_clean(stack_t *stack);

#endif
