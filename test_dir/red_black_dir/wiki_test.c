#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include <time.h>

#define NIL NULL
#define LEFT 0
#define RIGHT 1
#define left child[LEFT]
#define right child[RIGHT]

#define _child_dir(N) ( (N) == (N)->parent->right ? RIGHT : LEFT )

typedef enum rbcolor_e : uint8_t
{
    BLACK,
    RED
}   rbcolor_t;

typedef struct rbnode_s
{
    struct rbnode_s *parent;
    struct rbnode_s *child[2];
    int             key;
    rbcolor_t       color;
}   rbnode_t;

typedef struct rbtree_s
{
    rbnode_t *root;
}   rbtree_t;

static rbnode_t *_rotate_dir_root(rbtree_t *t, rbnode_t *n, uint8_t dir)
{
    rbnode_t *p = n->parent;
    rbnode_t *s = n->child[1 - dir];
    rbnode_t *c;

    assert(s != NIL);

    c = s->child[dir];
    n->child[1 - dir] = c;
    if (c != NIL) c->parent = n;
    s->child[dir] = n;
    n->parent = s;
    s->parent = p;
    if (p != NIL)
        p->child[n == p->right ? RIGHT : LEFT] = s;
    else
        t->root = s;
    return s;
}

/*
 *          A                       B
 *        /   \                   /   \
 *      x       B       ->      A       z
 *            /   \           /   \
 *          y       z       x       y
 *
 */

#define _rotate_dir(n, dir) _rotate_dir_root(t, n, dir)
#define _rotate_dir_left(n) _rotate_dir_root(t, n, LEFT)
#define _rotate_dir_right(n) _rotate_dir_root(t, n, RIGHT)

static void _rbinsert(rbtree_t *t, rbnode_t *n, rbnode_t *p, uint8_t dir)
{
    rbnode_t *g;
    rbnode_t *u;

    n->color = RED;
    n->left = NIL;
    n->right = NIL;
    n->parent = p;
    if (p == NIL) {
        t->root = n;
        return ;
    }
    p->child[dir] = n;
    do {
        if (p->color == BLACK) {
            /*CASE_I1: (P is black) */
            return;
        }
        if ((g = p->parent) == NIL)
            goto CASE_I4;
        dir = _child_dir(p);
        u = g->child[1 - dir];
        if (u == NIL || u->color == BLACK)
            goto CASE_I56; /* P red && U black */
        /*CASE_I2: P && U red */
        p->color = BLACK;
        u->color = BLACK;
        g->color = RED;
        n = g;
    } while ((p = n->parent) != NIL);
/*CASE_I3:*/
    return;
CASE_I4:
    p->color = BLACK;
    return;
CASE_I56: /* P red && U black */
    if (n == p->child[1 - dir]) {
        /* CASE_I5: (P red && U black && N inner grandchild of G */
        _rotate_dir(p, dir);
        n = p;
        p = g->child[dir];
    }
    /* CASE_I6: P red && U black && n outer grandchild of G */
    _rotate_dir(g, 1 - dir);
    p->color = BLACK;
    g->color = RED;
}

static rbnode_t *_create_rbnode(int key)
{
    rbnode_t *node = malloc(sizeof(rbnode_t));
    if (!node) return NULL;
    node->key = key;
    return node;
}

/* public */

int rbinsert(rbtree_t *tree, int key)
{
    assert(tree);
    rbnode_t *node = _create_rbnode(key);
    if (!node) return -1;
    rbnode_t *cur = NIL;
    rbnode_t *tmp = tree->root;
    int dir = 0;
//    printf("INSERT start\n");//TEST
    while (tmp) {
//        printf("INSERT while start\n");//TEST
        if (tmp->key == key) {
            return 0;
        }
        dir = (key > tmp->key);
        cur = tmp;
        tmp = tmp->child[dir];
//        printf("INSERT while end\n");//TEST
    }
//    printf("INSERT\n");//TEST
    _rbinsert(tree, node, cur, dir);
    return 0;
}

/* create */

rbtree_t *rbcreate(void)
{
    rbtree_t *t = malloc(sizeof(rbtree_t));
    if (!t) return NULL;
    t->root = NIL;
    return t;
}

/* free */

static void _rbfree(rbnode_t *node)
{
    if (node) {
        _rbfree(node->child[0]);
        _rbfree(node->child[1]);
        free(node);
    }
}

void rbfree(rbtree_t *tree)
{
    if (tree) _rbfree(tree->root);
}

/* print */

static void _rbprint(rbnode_t *node, int tabs)
{
    for (int i = 0; i < tabs; ++i) printf("\t");
    if (node) {
        printf("%d [%c]\n", node->key, node->color ? 'R' : 'B');
        _rbprint(node->child[0], tabs + 1);
        _rbprint(node->child[1], tabs + 1);
    } else {
        printf("NIL\n");
    }
}

void rbprint(rbtree_t *tree)
{
    assert(tree);
    _rbprint(tree->root, 0);
}

/* main */

int main(void)
{
    clock_t start, stop;
    //const int arr[] = { 8, 3, 1, 6, 4, 7, 10, 14, 13 };
    const int size = 5000000;//sizeof(arr) / sizeof(int);

    rbtree_t *tree = rbcreate();
    if (!tree) return 1;

    start = clock();
    for (int i = 0; i < size; ++i) {
        rbinsert(tree, i);//arr[i]);
    }
    for (int i = size << 1; i >= size; --i) {
        rbinsert(tree, i);//arr[i]);
    }
    stop = clock();
//    rbprint(tree);

    printf("time = %g s\n", (double)(stop - start) / CLOCKS_PER_SEC);
    rbfree(tree);
    getchar();//TEST
    return 0;
}
