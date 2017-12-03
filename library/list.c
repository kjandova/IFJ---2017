///////////////////////////////////////////////////////////////////////////////////////////////////
//
//	IFH 2017
//	list.c
//
//	citate: [Online: http://pseudomuto.com/development/2013/05/02/implementing-a-generic-linked-list-in-c/]
//
//  Edit: Vilém Faigel
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "list.h"


/*
*  @function list_new
*  @param    list *list
*  @param    int elementSize
*  @param    freeFunction freeFn
*/
void list_new(list *list, int elementSize) {
  assert(elementSize > 0);
  list->logicalLength = 0;
  list->elementSize = elementSize;
  list->head = list->tail = NULL;
}



/*
*  @function list_destroy
*  @param    list *list
*/
void list_destroy(list *list) {
  listNode *current;
  while(list->head != NULL) {
    current = list->head;
    list->head = current->next;

    free(current->data);
    free(current);
  }
}


/*
*  @function list_prepend
*  @param    list *list
*  @param    element
*/
void list_prepend(list *list, void *element) {
  listNode *node = malloc(sizeof(listNode));
  node->data = malloc(list->elementSize);
  memcpy(node->data, element, list->elementSize);

  node->next = list->head;
  list->head = node;

  // first node?
  if(!list->tail) {
    list->tail = list->head;
  }

  list->logicalLength++;
}


/*
*  @function list_append
*  @param    list *list
*  @param    void *element
*/
void list_append(list *list, void *element) {
  listNode *node = malloc(sizeof(listNode));
  node->data = malloc(list->elementSize);
  node->next = NULL;

  memcpy(node->data, element, list->elementSize);

  if(list->logicalLength == 0) {
    list->head = list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }

  list->logicalLength++;
}


/*
*  @function list_for_each
*  @param    list *list
*  @param    listIterator iterator
*/
void list_for_each(list *list, listIterator iterator) {
  assert(iterator != NULL);

  listNode *node = list->head;
  bool result = true;
  while(node != NULL && result) {
    result = iterator(node->data);
    node = node->next;
  }
}


/*
*  @function list_head
*  @param    list *list
*  @param    void *element
*  @param    bool removeFromList
*/
void list_head(list *list, void *element, bool removeFromList) {
  assert(list->head != NULL);

  listNode *node = list->head;
  memcpy(element, node->data, list->elementSize);

  if(removeFromList) {
    list->head = node->next;
    list->logicalLength--;

    free(node->data);
    free(node);
  }
}


/*
*  @function list_tail
*  @param    list *list
*  @param    void *element
*/
void list_tail(list *list, void *element) {
  assert(list->tail != NULL);
  listNode *node = list->tail;
  memcpy(element, node->data, list->elementSize);
}


/*
*  @function list_size
*  @param    list *list
*/
int list_size(list *list) {
  return list->logicalLength;
}
