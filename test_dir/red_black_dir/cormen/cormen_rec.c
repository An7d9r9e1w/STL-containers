#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#define RED 0
#define BLACK 1

typedef struct node_s
{
    struct node_s *left;
    struct node_s *right;
    int key;
    int color;
}   node_t;

typedef struct tree_s
{
    node_t *root;
    node_t *sentinel;
}   tree_t;

tree_t *new_tree(void)
{
    tree_t *t = malloc(sizeof(tree_t));
    t->sentinel = malloc(sizeof(node_t));
    t->root = t->sentinel;
    t->sentinel->color = BLACK;
    return t;
}

node_t *new_node(node_t *nil, const int key)
{
    node_t *n = malloc(sizeof(node_t));
    n->left = nil;
    n->right = nil;
    n->color = RED;
    n->key = key;
    return n;
}

void _free_tree(node_t *n, const node_t *sentinel)
{
    if (n != sentinel) {
        _free_tree(n->left, sentinel);
        _free_tree(n->right, sentinel);
        free(n);
    }
}

void free_tree(tree_t *t)
{
    if (t) {
        _free_tree(t->root, t->sentinel);
        free(t->sentinel);
        free(t);
    }
}

/*void rotate(tree_t *t, node_t *n, const int dir)
{
    node_t *c = n->child[1 - dir];
    n->child[1 - dir] = c->child[dir];
    if (c->child[dir] != t->sentinel) {
        c->child[dir]->parent = n;
    }
    c->parent = n->parent;
    if (n->parent != t->sentinel) {
        t->root = c;
    } else {
        n->parent->child[n == n->parent->child[1]] = c;
    }
    c->child[dir] = n;
    n->parent = c;
}*/

node_t *left_rotate(node_t *n)
{
    node_t *c = n->right;
    n->right = c->left;
    c->left = n;
    return c;
}

node_t *right_rotate(node_t *n)
{
    node_t *c = n->left;
    n->left = c->right;
    c->right = n;
    return c;
}

node_t *_insert(node_t *p, node_t *s, const int key)
{
    if (p == s) return new_node(s, key);
    if (key == p->key) return p;
    if (key < p->key)
        p->left = _insert(p->left, s, key);
    else
        p->right = _insert(p->right, s, key);
    if (p->left->color == RED && p->right->color == RED) {
        p->color = RED;
        p->left->color = BLACK;
        p->right->color = BLACK;
    } else if (p->left->color == RED) {
        if (p->left->right->color == RED) {
            p->left = left_rotate(p->left);
        }
        if (p->left->left->color == RED) {
            p->color = RED;
            p->left->color = BLACK;
            p = right_rotate(p);
        }
    } else if (p->right->color == RED) {
        if (p->right->left->color == RED) {
            p->right = right_rotate(p->right);
        }
        if (p->right->right->color == RED) {
            p->color = RED;
            p->right->color = BLACK;
            p = left_rotate(p);
        }
    }
    return p;
}

void insert(tree_t *t, const int key)
{
    t->sentinel->key = key;
    t->root = _insert(t->root, t->sentinel, key);
    t->root->color = BLACK;
}

void _print_tree(const node_t *const n, const node_t *const s, const int tabs)
{
    for (int i = 0; i < tabs; ++i)
        printf("    ");
    if (n != s) {
        printf("%d[%c]\n", n->key, n->color ? 'B' : 'R');
        _print_tree(n->left, s, tabs + 1);
        _print_tree(n->right, s, tabs + 1);
    } else {
        printf("NIL\n");
    }
}

void print_tree(const tree_t *const t)
{
    if (t) _print_tree(t->root, t->sentinel, 0);
}

#define SIZE 5000000

int main(void)
{
    clock_t start, stop;
    tree_t *t = new_tree();

    start = clock();
    for (int i = 0; i < SIZE; ++i)
        insert(t, i);
    for (int i = SIZE << 1; i >= SIZE; --i)
        insert(t, i);
    stop = clock();

//    print_tree(t);
    printf("time = %g s\n", (double)(stop - start) / CLOCKS_PER_SEC);

    free_tree(t);
    getchar();
    return 0;
}
