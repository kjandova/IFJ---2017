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
//  @File				tree_debug.c
//  @Description
//
///////////////////////////////////////////////////////////////////////////////////



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tree_debug.h"
#include "tree_p.h"

static void tree_node_dump(struct tree_node *node, size_t level, int dir)
{
	if (!node) return;

	tree_node_dump(node->left, level+1, DIR_LEFT);

	for (size_t i=0; i<level; i++)
		if (i+1 < level)
			putchar(' ');
		else if (dir == DIR_LEFT)
			putchar('/');
		else if (dir == DIR_RIGHT)
			putchar('\\');
		else
			putchar('-');

	printf("* %s: %p\n", node->key, node->payload);

	tree_node_dump(node->right, level+1, DIR_RIGHT);

	return;
}

void tree_dump(struct tree *t)
{
	tree_node_dump(t->root, 0, 0);
}
