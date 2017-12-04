///////////////////////////////////////////////////////////////////////////////////////////////////
//
//	IFH 2017
//	list.h
//
//	citate: [Online: http://pseudomuto.com/development/2013/05/02/implementing-a-generic-linked-list-in-c/]
//
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef IFJ_LIST_H
#define IFJ_LIST_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

// a common function used to free malloc'd objects


typedef bool (*listIterator)(void *);

typedef struct _listNode {
  void *data;
  struct _listNode *next;
} listNode;

typedef struct {
  int logicalLength;
  int elementSize;
  listNode *head;
  listNode *tail;
} list;

void list_new(list *list, int elementSize);
void list_destroy(list *list);

void list_prepend(list *list, void *element);
void list_append(list *list, void *element);
int list_size(list *list);

void list_for_each(list *list, listIterator iterator);
void list_head(list *list, void *element, bool removeFromList);
void list_tail(list *list, void *element);

void * list_index(list *list, int index);

#endif // IFJ_LIST_H
