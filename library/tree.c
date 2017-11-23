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
//  @File				tree.c
//  @Description
//
///////////////////////////////////////////////////////////////////////////////////



#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <err.h>

#include "tree.h"
#include "tree_p.h"
#include "define.h"

struct tree *new_tree(enum tree_type type)
{
	struct tree *ret = NULL;
	ret = malloc(sizeof(*ret));
	if (!ret)
		err(RUNTIME_ERROR, "runtime error");

	tree_init(ret, type);
	return ret;
}

void del_tree(struct tree **t)
{
	if (!*t)
		return;
	tree_tear(*t);
	free(*t);
	t = NULL;
}

struct tree *tree_init(struct tree *t, enum tree_type type)
{
	struct tree tmp = {
		.type = type,
	};
	*t = tmp;
	return t;
}

static void tree_node_destroy(struct tree_node *root)
{
	if (!root)
		return;

	tree_node_destroy(root->left);
	tree_node_destroy(root->right);
	free(root);
}

void tree_tear(struct tree *t)
{
	tree_node_destroy(t->root);
}

int tree_add(struct tree *t, char *key, void *payload)
{
	assert(t);
	if (t->type == TREE_PLAIN)
		return tree_node_add(&t->root, key, payload);
	return 0;
}
int tree_set(struct tree *t, char *key, void *payload)
{
	assert(t);
	if (t->type == TREE_PLAIN)
		return tree_node_set(&t->root, key, payload);
	return 0;
}
int tree_del(struct tree *t, char *key)
{
	assert(t);
	if (t->type == TREE_PLAIN)
		return tree_node_del(&t->root, key);
	return 0;
}

int tree_get(struct tree *t, char *key, void **payload)
{
	assert(t);
	return tree_node_get(&t->root, key, payload);
}

void tree_balance(struct tree *t)
{
	tree_node_dsw(&t->root);
	return;
}

static struct tree_node *tree_node_new(char *key, void *payload)
	__attribute__((warn_unused_result));

static struct tree_node *tree_node_new(char *key, void *payload)
{
	struct tree_node *ret = NULL;

	ret = calloc(1, sizeof(*ret));
	if (!ret)
		err(RUNTIME_ERROR, "runtime error");

	ret->key = key;
	ret->payload = payload;

	return ret;
}

static struct tree_node **tree_node_search(struct tree_node **root, char *key)
{
	struct tree_node **ret = root;

	assert(root);

	while (*ret) {
		int tmp = strcmp(key, (*ret)->key);
		if (tmp < 0)
			ret = &(*ret)->left;
		else if (tmp > 0)
			ret = &(*ret)->right;
		else
			return ret;
	}
	return ret;
}

/**
 * \return success boolean
 */
int tree_node_add(struct tree_node **root, char *key, void *payload)
{
	struct tree_node **tgt;

	tgt = tree_node_search(root, key);
	if (*tgt)
		return 0;

	*tgt = tree_node_new(key, payload);
	return 1;
}

int tree_node_set(struct tree_node **root, char *key, void *payload)
{
	struct tree_node *tgt;

	tgt = *(tree_node_search(root, key));
	if (!tgt)
		return 0;

	tgt->payload = payload;
	return 1;
}

static int rmnode(struct tree_node **node)
{
	struct tree_node *tgt, **repl;
	assert(node && *node);
	tgt = *node;
	if (!tgt->left && !tgt->right) {
	} else if (tgt->left && tgt->right) {
		// TODO: switch branches to avoid imbalanced branches
		if (1) {
			// Go to rightmost node of the left branch
			for (repl = &(*node)->left; (*repl)->right; repl = &(*repl)->right);
			*node = *repl;
			*repl = (*repl)->left;
		} else {
			// Go to leftmost node of the right branch
			for (repl = &(*node)->right; (*repl)->left; repl = &(*repl)->left);
			*node = *repl;
			*repl = (*repl)->right;
		}
		(*node)->left = tgt->left;
		(*node)->right = tgt->right;
	} else if (tgt->left) {
		*node = tgt->left;
	} else /*if (tgt->right)*/ {
		*node = tgt->right;
	}
	// TODO: unref payload
	free(tgt);
	return 1;
}

int tree_node_del(struct tree_node **root, char *key)
{
	struct tree_node **node = tree_node_search(root, key);
	if (!*node)
		return 0;
	return rmnode(node);
}

int tree_node_get(struct tree_node **root, char *key, void **payload)
{
	struct tree_node *tgt;

	if (payload)
		*payload = NULL;

	tgt = *(tree_node_search(root, key));
	if (!tgt) {
		return 0;
	} else {
		if (payload)
			*payload = tgt->payload;
		return 1;
	}
}

int tree_node_rotate(struct tree_node **root, int dir)
{
	struct tree_node *tmp;

	assert(root);

	if (!dir || !*root)
		return 0;

	tmp = *root;
	if (dir < 0) { // left
		if (!tmp->right)
			return 0;
		*root = tmp->right;
		tmp->right = (*root)->left;
		(*root)->left = tmp;
	} else { //right
		if (!tmp->left)
			return 0;
		*root = tmp->left;
		tmp->left = (*root)->right;
		(*root)->right = tmp;
	}
	return 1;
}

/**
 * Transforms tree to degraded linear tree
 * \return length of vine
 */
static int dsw_tree2vine(struct tree_node **root)
{
	int ret = 0;
	while (*root) {
		ret++;
		while (tree_node_rotate(root, DIR_RIGHT));
		root = &(*root)->right;
	}
	return ret;
}

/**
 * Transforms degraded linear tree to balanced tree
 * \param length length of tree, negative value for unknown
 * \return length of vine
 */
static void dsw_vine2tree(struct tree_node **root, int length)
{
	unsigned n, i;
	struct tree_node **tmp;

	if (length < 0) {
		struct tree_node *tmp2;
		length = 0;
		for (tmp2 = *root; tmp2; tmp2 = tmp2->right) {
			length++;
		}
	}

	/*
	 * tree has maximal capacity n = 2^h - 1 (0b1, 0b11, 0b111 and so on)
	 * find how much elements would make complete tree
	 */
	for (n=1; n <= length; n = n<<1 |1);
	n >>= 1;

	for (i = length - n, tmp = root; i > 0; i--) {
		tree_node_rotate(tmp, DIR_LEFT);
		tmp = &(*tmp)->right;
	}

	for (n >>= 1; n > 0; n >>= 1) {
		for (i = n, tmp = root; i > 0; i--) {
			tree_node_rotate(tmp, DIR_LEFT);
			tmp = &(*tmp)->right;
		}
	}
}

/**
 * Tree balancing using Day-Stout-Warren algorithm
 */
void tree_node_dsw(struct tree_node **root)
{
	int length;

	length = dsw_tree2vine(root);
	dsw_vine2tree(root, length);
}
