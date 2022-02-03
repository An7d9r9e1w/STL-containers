#include <stdio.h>
#include <stdlib.h>

#include <time.h>

int *rand_set(const size_t size);
void print_arr(const int *arr, const size_t size);

#define RED 0
#define BLACK 1

typedef struct node_s
{
    struct node_s *left;
    struct node_s *right;
    int color;
    int value;
}   node_t;

typedef struct tree_s
{
    node_t *root;
}   tree_t;

tree_t *new_tree(void)
{
    tree_t *t = malloc(sizeof(tree_t));
    t->root = NULL;
    return t;
}

node_t *new_node(int value)
{
    node_t *n = malloc(sizeof(node_t));
    n->value = value;
    n->left = NULL;
    n->right = NULL;
    n->color = RED;
    return n;
}

node_t *rotate_left(node_t *h)
{
    node_t *x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

node_t *rotate_right(node_t *h)
{
    node_t *x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

void flip_colors(node_t *h)
{
    h->color = !h->color;
    h->left->color = !h->left->color;
    h->right->color = !h->right->color;
}

node_t *_insert(node_t *n, int value)
{
    if (!n) return new_node(value);

    if (n->left && n->left->color == RED &&
        n->right && n->right->color == RED)
        flip_colors(n);

    if (n->value == value) {}
    else if (value < n->value)
        n->left = _insert(n->left, value);
    else
        n->right = _insert(n->right, value);

    if (n->right && n->right->color == RED &&
        (!n->left || n->left->color == BLACK))
        n = rotate_left(n);
    if (n->left && n->left->color == RED &&
        n->left->left && n->left->left->color == RED)
        n = rotate_right(n);
    return n;
}

void insert(tree_t *t, int value)
{
    t->root = _insert(t->root, value);
    t->root->color = BLACK;
}

void _print_tree(node_t *n, int tabs)
{
    for (int i = 0; i < tabs; ++i)
        printf("    ");
    if (n) {
        printf("%d[%c]\n", n->value, n->color ? 'B' : 'R');
        _print_tree(n->left, tabs + 1);
        _print_tree(n->right, tabs + 1);
    } else {
        printf("NULL\n");
    }
}

void print_tree(tree_t *t)
{
    _print_tree(t->root, 0);
}

void _free_tree(node_t *n)
{
    if (n) {
        _free_tree(n->left);
        _free_tree(n->right);
        free(n);
    }
}

void free_tree(tree_t *t)
{
    if (t) {
        _free_tree(t->root);
        free(t);
    }
}

#define SIZE 5000000

int main(void)
{
    clock_t start, stop;
//    int *set = rand_set(SIZE);

//    print_arr(set, SIZE);

    tree_t *t = new_tree();

//    for (int i = 0; i < SIZE; ++i)
//        insert(t, set[i]);
    start = clock();
    for (int i = 0; i < SIZE; ++i)
        insert(t, i);
    for (int i = SIZE << 1; i >= SIZE; --i)
        insert(t, i);
    stop = clock();

//    print_tree(t);
    printf("time = %g s\n", (double)(stop - start) / CLOCKS_PER_SEC);

//    print_tree(t);

    free_tree(t);
//    free(set);
    getchar();
    return 0;
}
