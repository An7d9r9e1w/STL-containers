#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

enum color_e
{
	RED,
	BLACK
};

struct node_s
{
	struct node_s *parent;
	struct node_s *left;
	struct node_s *right;
	int	value;
	int8_t color;
};

typedef struct node_s node_t;

void insert_case1(node_t **root, node_t *n);
void insert_case2(node_t **root, node_t *n);
void insert_case3(node_t **root, node_t *n);
void insert_case4(node_t **root, node_t *n);
void insert_case5(node_t **root, node_t *n);

/// others
node_t *create_node(int value)
{
	node_t *node = malloc(sizeof(node_t));
	if (!node) return NULL;
	node->value = value;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->color = RED;
	return node;
}
/*
void destroy(node_t *n)
{
	if (n) {
		destroy(n->left);
		destory(n->right);
		free(n);
	}
}
*/
void destroy/*_tree*/(node_t *n)
{
//	destroy(n);
	while (n) {
		if (n->left) {
			n = n->left;
			n->parent->left = NULL;
		} else if (n->right) {
			n = n->right;
			n->parent->right = NULL;
		} else {
			node_t *tmp = n;
			n = n->parent;
			free(tmp);
		}
	}
}

void print_node_value(node_t *n, int tabs)
{
	while (tabs--)
		printf("\t");
	if (n) {
		printf("%d[%c]\n", n->value, (n->color == BLACK) ? 'B' : 'R');
	} else {
		printf("*[B]\n");
	}
}

void print_node(node_t *n, int tabs)
{
	print_node_value(n, tabs);
	if (n && tabs < 10) {
		print_node(n->left, tabs + 1);
		print_node(n->right, tabs + 1);
	}
}

void print_tree(node_t *n)
{
	print_node(n, 0);
}

node_t *grandparent(node_t *node)
{
	if (node && node->parent)
		return node->parent->parent;
	return NULL;
}

node_t *uncle(node_t *node)
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
node_t *rotate_left(node_t *n)
{
	node_t *pivot = n->right;
	pivot->parent = n->parent;
	if (n->parent) {
		if (n->parent->left == n)
			n->parent->left = pivot;
		else
			n->parent->right = pivot;
	}
	n->right = pivot->left;
	if (pivot->left)
		pivot->left->parent = n;
	pivot->left = n;
	n->parent = pivot;
	return pivot;
}

node_t *rotate_right(node_t *n)
{
	node_t *pivot = n->left;
	pivot->parent = n->parent;
	if (n->parent) {
		if (n->parent->left == n)
			n->parent->left = pivot;
		else
			n->parent->right = pivot;
	}
	n->left = pivot->right;
	if (pivot->right)
		pivot->right->parent = n;
	pivot->right = n;
	n->parent = pivot;
	return pivot;
}

/// insert
int insert(node_t **root, int value)
{
	if (!root) return -1;
	node_t *n = create_node(value);
	if (!n) return -1;

	if (*root) {
		node_t *tmp = *root;
		while (1) {
			if (value < tmp->value) {
				if (!tmp->left) {
					tmp->left = n;
					break;
				}
				tmp = tmp->left;
			} else {
				if (!tmp->right) {
					tmp->right = n;
					break;
				}
				tmp = tmp->right;
			}
		}
		n->parent = tmp;
	} else {
		*root = n;
	}
//	print_tree(*root);
	printf("CASES [");//TEST
	insert_case1(root, n);
	printf(" ]\n");//TEST
	return 0;
}

void insert_case1(node_t **root, node_t *n)
{
	printf(" 1");//TEST
	if (!n->parent)	{	// n is root
		n->color = BLACK;
	} else {
		insert_case2(root, n);
	}
}

void insert_case2(node_t **root, node_t *n)
{
	printf(" 2");//TEST
	if (n->parent->color != BLACK) {	// black path is same
		insert_case3(root, n);
	}
}

void insert_case3(node_t **root, node_t *n)
{
	printf(" 3");//TEST
	node_t *u = uncle(n);
	node_t *g;
	if (u && u->color == RED) {
		u->color = BLACK;
		n->parent->color = BLACK;
		g = grandparent(n);
		g->color = RED;
		insert_case1(root, g);
	} else {
		insert_case4(root, n);
	}
}

void insert_case4(node_t **root, node_t *n)
{
	printf(" 4");//TEST
	node_t *g = grandparent(n);
	if ((n == n->parent->right) && (n->parent == g->left)) {
		node_t *tmp_p = g->left;
		node_t *tmp_l = n->left;
		g->left = n;
		n->left = tmp_p;
		tmp_p->right = tmp_l;
		n = n->left;
	} else if ((n == n->parent->left) && (n->parent == g->right)) {
		node_t *tmp_p = g->right;
		node_t *tmp_r = n->right;
		g->right = n;
		n->right = tmp_p;
		tmp_p->left = tmp_r;
		n = n->right;
	}
	insert_case5(root, n);
}

void rotate(node_t **root, node_t *n, node_t *(*r)(node_t *n))
{
	if (*root == n) {
		*root = r(n);
	} else if (n->parent->left == n) {
//		print_node_value(n->parent->left, 0);//TEST
//		n->parent->left = r(n);
		r(n);
	} else {
//		print_node_value(n->parent->right, 0);//TEST
//		n->parent->right = r(n);
		r(n);
	}
}

void insert_case5(node_t **root, node_t *n)
{
	printf(" 5");//TEST
	node_t *g = grandparent(n);
	n->parent->color = BLACK;
	g->color = RED;
	if ((n == n->parent->left) && (n->parent == g->left)) {
		rotate(root, g, rotate_right);
	} else {
		rotate(root, g, rotate_left);
	}
}

///fill
node_t *random_tree(int size)
{
	srand(clock());
	node_t *root = NULL;//create_node(rand() % size);
//	if (!root) return NULL;
//	root->color = BLACK;
	for (int i = 0; i < size; ++i) {
//		printf("START [%d]\n", i);//TEST
		if (insert(&root, rand() % size) == -1) {
			destroy(root);
			return NULL;
		}
//		printf("NEXT\n");//TEST
	}
	return root;
}

/// main
void test_rotate()
{
	node_t *n = create_node(2);
	insert(&n, 1);
	insert(&n, 4);
	insert(&n, 3);
	insert(&n, 5);
	print_tree(n);
	n = rotate_left(n);
	print_tree(n);
	n->left = rotate_left(n->left);
	print_tree(n);
	n = rotate_right(n);
	print_tree(n);
	destroy(n);
}

void test_insert()
{
	node_t *n = NULL;
	insert(&n, 5);
	print_tree(n);
	insert(&n, 6);
	print_tree(n);
	insert(&n, 7);
	print_tree(n);
	destroy(n);
}

void test_insert2()
{
	node_t *n = NULL;
	for (int i = 5; i < 10; ++i) {
		printf("---- [%d] ----\n", i + 1);
		insert(&n, i + 1);
		print_tree(n);
	}
	for (int i = 0; i < 5; ++i) {
		printf("---- [%d] ----\n", i + 1);
		insert(&n, i + 1);
		print_tree(n);
	}
	destroy(n);
}

int main()
{
/*	node_t *tree = random_tree(10);
	if (!tree) return 1;
	print_tree(tree);
	destroy(tree);*/
//	test_rotate();
//	test_insert();
	test_insert2();
	getchar();
	return 0;
}
