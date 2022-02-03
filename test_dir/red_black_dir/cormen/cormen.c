#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#define RED 0
#define BLACK 1

typedef struct node_s
{
    struct node_s *parent;
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

void left_rotate(tree_t *t, node_t *n)
{
    node_t *c = n->right;
    n->right = c->left;
    if (c->left != t->sentinel) {
        c->left->parent = n;
    }
    c->parent = n->parent;
    if (n->parent == t->sentinel) {
        t->root = c;
    } else if (n == n->parent->left) {
        n->parent->left = c;
    } else {
        n->parent->right = c;
    }
    c->left = n;
    n->parent = c;
}

void right_rotate(tree_t *t, node_t *n)
{
    node_t *c = n->left;
    n->left = c->right;
    if (c->right != t->sentinel) {
        c->right->parent = n;
    }
    c->parent = n->parent;
    if (n->parent == t->sentinel) {
        t->root = c;
    } else if (n == n->parent->left) {
        n->parent->left = c;
    } else {
        n->parent->right = c;
    }
    c->right = n;
    n->parent = c;
}

void _insert_fixup(tree_t *t, node_t *n)
{
    node_t *s;
    while (n->parent->color == RED) {
        if (n->parent == n->parent->parent->left) {
            s = n->parent->parent->right;
            if (s->color == RED) {
                n->parent->color = BLACK;
                s->color = BLACK;
                n = n->parent->parent;
                n->color = RED;
            } else {
                if (n == n->parent->right) {
                    n = n->parent;
                    left_rotate(t, n);
                }
                n->parent->color = BLACK;
                n->parent->parent->color = RED;
                right_rotate(t, n->parent->parent);
            }
        } else {
            s = n->parent->parent->left;
            if (s->color == RED) {
                n->parent->color = BLACK;
                s->color = BLACK;
                n = n->parent->parent;
                n->color = RED;
            } else {
                if (n == n->parent->left) {
                    n = n->parent;
                    right_rotate(t, n);
                }
                n->parent->color = BLACK;
                n->parent->parent->color = RED;
                left_rotate(t, n->parent->parent);
            }
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
        if (key < tmp->key) {
            tmp = tmp->left;
        } else {
            tmp = tmp->right;
        }
    }
    if (tmp != t->sentinel) {
        return;
    }
    node_t *n = new_node(t, cur, key);
    if (key < cur->key) {
        cur->left = n;
    } else {
        cur->right = n;
    }
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

void _transplant(tree_t *t, node_t *p, node_t *n)
{
    if (p->parent == t->sentinel) {
        t->root = n;
    } else if (p == p->parent->left) {
        p->parent->left = n;
    } else {
        p->parent->right = n;
    }
    n->parent = p->parent;
}

node_t *_get_min(const tree_t *const t, const node_t *n)
{
    while (n->left != t->sentinel) {
        n = n->left;
    }
    return (node_t *)n;
}

void _delete_fixup(tree_t *t, node_t *n)
{
    node_t *s;
    while (n != t->root && n->color == BLACK) {
        if (n == n->parent->left) {
            s = n->parent->right;
            if (s->color == RED) {
                s->color = BLACK;
                n->parent->color = RED;
                left_rotate(t, n->parent);
                s = n->parent->right;
            }
            if (s->left->color == BLACK && s->right->color == BLACK) {
                s->color = RED;
                n = n->parent;
            } else {
                if (s->right->color == BLACK) {
                    s->left->color = BLACK;
                    s->color = RED;
                    right_rotate(t, s);
                    s = n->parent->right;
                }
                s->color = n->parent->color;
                n->parent->color = BLACK;
                s->right->color = BLACK;
                left_rotate(t, n->parent);
                n = t->root;
            }
        } else {
            s = n->parent->left;
            if (s->color == RED) {
                s->color = BLACK;
                n->parent->color = RED;
                right_rotate(t, n->parent);
                s = n->parent->left;
            }
            if (s->left->color == BLACK && s->right->color == BLACK) {
                s->color = RED;
                n = n->parent;
            } else {
                if (s->left->color == BLACK) {
                    s->right->color = BLACK;
                    s->color = RED;
                    left_rotate(t, s);
                    s = n->parent->left;
                }
                s->color = n->parent->color;
                n->parent->color = BLACK;
                s->left->color = BLACK;
                right_rotate(t, n->parent);
                n = t->root;
            }
        }
    }
    n->color = BLACK;
}

void _delete(tree_t *t, node_t *n)
{
    node_t *x;
    node_t *y = n;
    int y_color = n->color;
    if (n->left == t->sentinel) {
        x = n->right;
        _transplant(t, n, n->right);
    } else if (n->right == t->sentinel) {
        x = n->left;
        _transplant(t, n, n->left);
    } else {
        y = _get_min(t, n->right);
        y_color = y->color;
        x = y->right;
        if (y->parent == n) {
            x->parent = y;
        } else {
            _transplant(t, y, y->right);
            y->right = n->right;
            y->right->parent = y;
        }
        _transplant(t, n, y);
        y->left = n->left;
        y->left->parent = y;
        y->color = n->color;
    }
    if (y_color == BLACK) {
        _delete_fixup(t, x);
    }
}

void delete(tree_t *t, const int key)
{
    t->sentinel->key = key;
    node_t *cur = t->root;
    while (key != cur->key) {
        cur = (key < cur->key) ? (cur->left) : (cur->right);
    }
    if (cur != t->sentinel) {
        _delete(t, cur);
        free(cur);
    }
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

#define SIZE 1000000

int *rand_set(const size_t size);

int main(void)
{
    clock_t start, stop;
    int *set = rand_set(SIZE);
    tree_t *t = new_tree();

    start = clock();
    for (int i = 0; i < SIZE; ++i)
        insert(t, set[i]);
//    for (int i = SIZE << 1; i >= SIZE; --i)
//        insert(t, i);
    stop = clock();

//    print_tree(t);
    printf("time = %g s\n", (double)(stop - start) / CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < SIZE; ++i)
        delete(t, i + 1);
    stop = clock();
//    print_tree(t);
    printf("time = %g s\n", (double)(stop - start) / CLOCKS_PER_SEC);

    free_tree(t);
    getchar();
    return 0;
}
