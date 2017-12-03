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

///////////////////////////////////////////////////////////////////////////////////
//
//  TREE
//

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

#endif // IFJ_TREE_H


///////////////////////////////////////////////////////////////////////////////////
//
//  TREE NODE
//

#ifndef IFJ_TREE_P_H
#define IFJ_TREE_P_H
// Private headers for tree implementation
// Lower-level functions

#define DIR_LEFT -1
#define DIR_RIGHT 1

struct tree_node {
	struct tree_node *left;
	struct tree_node *right;
	int balance;
	char *key;
	void *payload;
};

int tree_node_add(struct tree_node **root, char *key, void *payload);
int tree_node_set(struct tree_node **root, char *key, void *payload);
int tree_node_del(struct tree_node **root, char *key);
int tree_node_get(struct tree_node **root, char *key, void **payload);

int tree_node_rotate(struct tree_node **root, int dir);

/* Day-Stout-Warren */
void tree_node_dsw(struct tree_node **root);

#endif // IFJ_TREE_P_H
