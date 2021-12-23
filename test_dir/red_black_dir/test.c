#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum color_e
{
	RED,
	BLACK
};

struct node_s
{
	void *data;
	struct node_s *parent;
	struct node_s *left;
	struct node_s *right;
	int8_t color;
};

typedef struct node_s node_t;

/// others
node_t *create_node(void *data)
{
	node_t *node = malloc(sizeof(node_t));
	if (!node) return NULL;
	node->data = data;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->color = RED;
	return node;
}

node_t grandparent(node_t *node)
{
	if (node && node->parent)
		return node->parent->parent;
	return NULL;
}

node_t uncle(node_t *node)
{
	node_t *grand = grandparent(node);
	if (!grand) return NULL;
	if (node->parent == grand->left)
		return grand->right;
	return grand->left;
}

/*
left rotate

		  r						  r
		 /						 /
		n						p
	  /   \					  /   \
	x		p				n		pr
  /   \   /   \			  /	  \
 *     * pl    pr		x	   pl
 					  /   \
					 *	   *

*/

/// rotate
void rotate_left(node_t *node)
{
	node_t *pivot = node_t->right;
	pivot->parent = node->parent;
	if (node->parent) {
		if (node->parent->left == node)
			node->parent->left = pivot;
		else
			node->parent->right = pivot;
	}
	node->right = pivot->left;
	if (pivot->left)
		pivot->left->parent = node;
	node->parent = pivot;
	pivot->left = node;
}

void rotate_right(node_t *node)
{
	node_t *pivot = node_t->left;
	pivot->parent = node->parent;
	if (node->parent) {
		if (node->parent->left == node)
			node->parent->left = pivot;
		else
			node->parent->right = pivot;
	}
	node->left = pivot->right;
	if (pivot->right)
		pivot->right->parent = node;
	node->parent = pivot;
	pivot->right = node;
}

/// insert
void insert_case1(node_t *node);
void insert_case2(node_t *node);
void insert_case3(node_t *node);
void insert_case4(node_t *node);
void insert_case5(node_t *node);

void insert_case1(node_t *node)
{
	if (!node->parent)	// node is root
		node->color = BLACK;
	else
		insert_case2(node);
}

void insert_case2(node_t *node)
{
	if (node->parent->color == BLACK)	// black path is same
		return;
	else
		insert_case3(node);
}

/// main
int main()
{
	return 0;
}
