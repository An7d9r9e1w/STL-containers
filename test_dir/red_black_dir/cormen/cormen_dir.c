#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#define RED 0
#define BLACK 1

#define LEFT 0
#define RIGHT 1
#define left child[LEFT]
#define right child[RIGHT]

typedef struct node_s
{
    struct node_s *parent;
    struct node_s *child[2];
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

node_t *new_node(tree_t *t, node_t *p, int key)
{
    node_t *n = malloc(sizeof(node_t));
    n->parent = p;
    n->left = t->sentinel;
    n->right = t->sentinel;
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

void rotate(tree_t *t, node_t *n, const int dir)
{
    node_t *c = n->child[1 - dir];
    n->child[1 - dir] = c->child[dir];
    if (c->child[dir] != t->sentinel) {
        c->child[dir]->parent = n;
    }
    c->parent = n->parent;
    if (n->parent == t->sentinel) {
        t->root = c;
    } else {
        n->parent->child[n == n->parent->child[1]] = c;
    }
    c->child[dir] = n;
    n->parent = c;
}

void _insert_fixup(tree_t *t, node_t *n)
{
    node_t *s;
    while (n->parent->color == RED) {
        int dir = (n->parent == n->parent->parent->left);
        s = n->parent->parent->child[dir];
        if (s->color == RED) {
            n->parent->color = BLACK;
            s->color = BLACK;
            n = n->parent->parent;
            n->color = RED;
        } else {
            if (n == n->parent->child[dir]) {
                n = n->parent;
                rotate(t, n, 1 - dir);
            }
            n->parent->color = BLACK;
            n->parent->parent->color = RED;
            rotate(t, n->parent->parent, dir);
        }
    }
}

void _insert(tree_t *t, const int key)
{
    node_t *tmp = t->root;
    node_t *cur = t->sentinel;
    cur->key = key;
    while (key != tmp->key) {
        cur = tmp;
        tmp = tmp->child[key > tmp->key];
    }
    if (tmp != t->sentinel) {
        return;
    }
    node_t *n = new_node(t, cur, key);
    cur->child[key > cur->key] = n;
    _insert_fixup(t, n);
}

void insert(tree_t *t, const int key)
{
    if (t->root == t->sentinel) {
        t->root = new_node(t, t->sentinel, key);
    } else {
        _insert(t, key);
    }
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
//    clock_t start, stop;
    tree_t *t = new_tree();

/*    start = clock();
    for (int i = 0; i < SIZE; ++i)
        insert(t, i);
    for (int i = SIZE << 1; i >= SIZE; --i)
        insert(t, i);
    stop = clock();*/

    int arr[] = { 13, 5, 15, 6, 9, 2, 3, 1, 4, 7, 14, 10, 12, 8, 11 };
    int size = sizeof(arr) / sizeof(int);
    for (int i = 0; i < size; ++i)
        insert(t, arr[i]);
    print_tree(t);
//    printf("time = %g s\n", (double)(stop - start) / CLOCKS_PER_SEC);

    free_tree(t);
//    getchar();
    return 0;
}
