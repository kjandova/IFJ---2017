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
//  @File				tree.h
//  @Description
//
///////////////////////////////////////////////////////////////////////////////////



#ifndef IFJ_TREE_H
#define IFJ_TREE_H

enum tree_type {
	TREE_PLAIN,
// 	TREE_AVL,
};

struct tree {
	struct tree_node *root;
	enum tree_type type;
	unsigned readonly : 1;
};

struct tree *new_tree(enum tree_type type)
  __attribute__((warn_unused_result));
void del_tree(struct tree **t);

struct tree *tree_init(struct tree *t, enum tree_type type);
void tree_tear(struct tree *t);

int tree_add(struct tree *t, char *key, void *payload);
int tree_set(struct tree *t, char *key, void *payload);
int tree_del(struct tree *t, char *key);

int tree_get(struct tree *t, char *key, void **payload);

void tree_balance(struct tree *t);

#endif
