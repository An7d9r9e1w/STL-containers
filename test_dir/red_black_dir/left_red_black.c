#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include <time.h>

#define LEFT 0
#define RIGHT 1

#define left child[LEFT]
#define right child[RIGHT]

int *rand_set(const size_t size);

typedef enum lrbcolor_e : uint8_t
{
    RED,
    BLACK
}   lrbcolor_t;

typedef struct lrbnode_s
{
    struct lrbnode_s *parent;
    struct lrbnode_s *child[2];
    int key;
    lrbcolor_t color;
}   lrbnode_t;

typedef struct lrbtree_s
{
    lrbnode_t *root;
    lrbnode_t *sentinel;
}   lrbtree_t;


lrbtree_t *lrbtree_create(void)
{
    lrbtree_t *t = malloc(sizeof(lrbtree_t));
    if (!t) return NULL;
    t->sentinel = malloc(sizeof(lrbnode_t));
    if (!t->sentinel) {
        free(t);
        return NULL;
    }
    t->sentinel->left = NULL;
    t->sentinel->right = NULL;
    t->sentinel->parent = NULL;
    t->sentinel->color = BLACK;
    t->root = t->sentinel;
    return t;
}

lrbnode_t *_lrbnode_create(const lrbtree_t *t, lrbnode_t *p, const int key)
{
    lrbnode_t *n = malloc(sizeof(lrbnode_t));
    if (!n) return NULL;
    n->parent = p;
    n->left = t->sentinel;
    n->right = t->sentinel;
    n->key = key;
    return n;
}

void _lrbfree(lrbnode_t *s, lrbnode_t *n)
{
    if (n != s) {
        _lrbfree(s, n->left);
        _lrbfree(s, n->right);
        free(n);
    }
}

void lrbfree(lrbtree_t *t)
{
    if (t) {
        _lrbfree(t->sentinel, t->root);
        free(t->sentinel);
        free(t);
    }
}

lrbnode_t *_lrbsearch(const lrbtree_t *t, const int key)
{
    lrbnode_t *n = t->root;
    lrbnode_t *tmp = n;
    t->sentinel->key = key;
    while (tmp->key != key) {
        n = tmp;
        tmp = tmp->child[key > tmp->key];
    }
    if (tmp == t->sentinel) return n;
    return tmp;
}

void _lrbrotate(lrbtree_t *t, lrbnode_t *p, int dir)
{
    lrbnode_t *c = p->child[dir];
    p->child[dir] = p->parent;
    p->parent->child[p == p->parent->right] = c;
    c->parent = p->parent;
    p->parent = p->child[dir]->parent;
    p->parent->child[p->child[dir] == p->parent->right] = p;
    p->child[dir]->parent = p;
    if (p->parent == t->sentinel) {
        t->root = p;
        p->color = BLACK;
    } else {
        p->color = p->child[dir]->color;
    }
    p->child[dir]->color = RED;
}

int lrbinsert(lrbtree_t *t, int key)
{
    assert(t);
    lrbnode_t *p = _lrbsearch(t, key);
    if (p != t->sentinel && p->key == key) return 0;
    lrbnode_t *n = _lrbnode_create(t, p, key);
    if (!n) return -1;
    if (p == t->sentinel) {
        t->root = n;
        n->color = BLACK;
        return 0;
    }
    p->child[key > p->key] = n;
    do {
        if (p->left->color == RED) {
            if (p->color == RED)
                _lrbrotate(t, p, RIGHT);
            else if (p->right->color == BLACK)
                break;
            p->left->color = BLACK;
            p->right->color = BLACK;
            if (p != t->root) p->color = RED;
        } else if (p->right->color == RED) {
            _lrbrotate(t, p->right, LEFT);
        } else {
            break;
        }
        p = p->parent;
    } while (p != t->sentinel);
    return 0;
}

void _lrbprintt(lrbnode_t *n, lrbnode_t *s, int tabs)
{
    for (int i = 0; i < tabs; ++i)
        printf("    ");
    if (n != s) {
        printf("%d[%c]\n", n->key, n->color ? 'B' : 'R');
        _lrbprintt(n->left, s, tabs + 1);
        _lrbprintt(n->right, s, tabs + 1);
    } else {
        printf("NULL\n");
    }
}

void lrbprint_as_tree(lrbtree_t *t)
{
    if (t) _lrbprintt(t->root, t->sentinel, 0);
}

void _lrbprintl(lrbnode_t *n, lrbnode_t *s)
{
    if (n != s) {
        _lrbprintl(n->left, s);
        printf("%d ", n->key);
        _lrbprintl(n->right, s);
    }
}

void lrbprint_as_list(lrbtree_t *t)
{
    printf("{ ");
    if (t) {
        _lrbprintl(t->root, t->sentinel);
    }
    printf("}\n");
}

#define SIZE 1000000

int main(void)
{
    lrbtree_t *t = lrbtree_create();

    int *set = rand_set(SIZE);

    clock_t start, stop;

    start = clock();
    for (int i = 0; i < SIZE; ++i) {
        lrbinsert(t, set[i]);
    }
    stop = clock();

//    lrbprint_as_tree(t);
//    lrbprint_as_list(t);
    printf("time = %g s\n", (double)(stop - start) / CLOCKS_PER_SEC);

    lrbfree(t);
    free(set);
//    getchar();
    return 0;
}
