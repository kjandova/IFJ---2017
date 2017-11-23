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
//  @File				tree_p.h
//  @Description
//
///////////////////////////////////////////////////////////////////////////////////


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

#endif
