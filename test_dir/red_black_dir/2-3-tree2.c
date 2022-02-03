#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int *rand_set(const size_t size);
void print_arr(const int *arr, const size_t size);

typedef struct ttnode_s
{
    struct ttnode_s *parent;
    struct ttnode_s *child[4];
    int vals[3];
    int type;
}   ttnode_t;

typedef struct tttree_s
{
    ttnode_t *root;
}   tttree_t;

static ttnode_t *_ttsearch_border(tttree_t *tree, int key)
{
    ttnode_t *cur = NULL;
    ttnode_t *tmp = tree->root;
    int dir = 0;
    while (tmp) {
        switch (tmp->type) {
        case 1:
            if (tmp->vals[0] == key) return tmp;
            cur = tmp;
            tmp = tmp->child[(key > tmp->vals[0]) << 1];
            break;
        case 2:
            if (tmp->vals[0] == key || tmp->vals[1] == key)
                return tmp;
            cur = tmp;
            if (key < tmp->vals[0])
                tmp = tmp->child[0];
            else
                tmp = tmp->child[1 + (key > tmp->vals[1])];
            break;
        }
    }
    return cur;
}

static int ttsearch(tttree_t *tree, int key)
{
    ttnode_t *p = _ttsearch_border(tree, key);
    if (p && (p->vals[0] == key || (p->type == 2 && p->vals[1] == key)))
        return key;
    return -1;
}

static ttnode_t *_ttnode_create(ttnode_t *p, int value)
{
    ttnode_t *node = malloc(sizeof(ttnode_t));
    node->vals[0] = value;
    node->type = 1;
    node->child[0] = NULL;
    node->child[1] = NULL;
    node->child[2] = NULL;
    node->parent = p;
    return node;
}

static void _ttinsert_case1(tttree_t *t, ttnode_t *p, int value);

static void _ttinsert_into_2node(ttnode_t *n, int value)
{
    if (n->vals[0] < value) {
        n->vals[1] = value;
    } else {
        n->vals[1] = n->vals[0];
        n->vals[0] = value;
    }
    n->type++;
}

static int _ttinsert_into_3node(ttnode_t *n, int value)
{
    if (value < n->vals[0]) {
        n->vals[2] = n->vals[0];
        n->vals[0] = value;
        return n->vals[2];
    } else if (value > n->vals[1]) {
        n->vals[2] = n->vals[1];
        n->vals[1] = value;
        return n->vals[2];
    }
    return value;
}

static void _ttchild_distribute(ttnode_t *left, ttnode_t *right)
{
    if (left->child[0]) {
        right->child[0] = left->child[2];
        right->child[2] = left->child[3];
        right->child[0]->parent = right;
        right->child[2]->parent = right;
        left->child[2] = left->child[1];
    }
}

static void _ttinsert_case1(tttree_t *t, ttnode_t *p, int value)
{
    ttnode_t *s;
    int mid;

    if (!p) {
        t->root = _ttnode_create(NULL, value);
        return;
    }
    if (p->type == 1) {
        _ttinsert_into_2node(p, value);//CASE 2
    } else if (p->parent) {
        //CASE 4
        ttnode_t *g = p->parent;
        mid = _ttinsert_into_3node(p, value);
        s = _ttnode_create(g, p->vals[1]);
        p->type--;
        _ttchild_distribute(p, s);
        while (g->type == 2) {
            if (g->child[0] == p) {
                g->child[3] = g->child[2];
                g->child[2] = g->child[1];
                g->child[1] = s;
            } else if (g->child[1] == p) {
                g->child[3] = g->child[2];
                g->child[2] = s;
            } else {
                g->child[3] = s;
            }
            if (g->parent) {
                p = g;
                g = g->parent;
                value = mid;
                mid = _ttinsert_into_3node(p, value);
                s = _ttnode_create(g, p->vals[1]);
                p->type--;
                _ttchild_distribute(p, s);
            } else {
                value = mid;
                goto CASE3;
            }
        }
        if (g->child[0] == p) {
            g->child[1] = s;
        } else {
            g->child[1] = p;
            g->child[2] = s;
        }
        _ttinsert_into_2node(g, mid);//CASE 2
    } else {
CASE3:
        mid = _ttinsert_into_3node(t->root, value);
        p = _ttnode_create(NULL, mid);
        s = _ttnode_create(p, t->root->vals[1]);
        _ttchild_distribute(t->root, s);
        t->root->type--;
        p->child[0] = t->root;
        p->child[2] = s;
        t->root->parent = p;
        t->root = p;
    }
}

static void ttinsert(tttree_t *t, int value)
{
    ttnode_t *p = _ttsearch_border(t, value);
    ttnode_t *s;
    int mid;

    if (!p) {
        t->root = _ttnode_create(NULL, value);
        return;
    }
    if (p->type == 1) {
        _ttinsert_into_2node(p, value);//CASE 2
    } else if (p->parent) {
        ttnode_t *g = p->parent;
        mid = _ttinsert_into_3node(p, value);
        s = _ttnode_create(g, p->vals[1]);
        p->type--;
        _ttchild_distribute(p, s);
        while (g->type == 2) {
            if (g->child[0] == p) {
                g->child[3] = g->child[2];
                g->child[2] = g->child[1];
                g->child[1] = s;
            } else if (g->child[1] == p) {
                g->child[3] = g->child[2];
                g->child[2] = s;
            } else {
                g->child[3] = s;
            }
            if (g->parent) {
                p = g;
                g = g->parent;
                value = mid;
                mid = _ttinsert_into_3node(p, value);
                s = _ttnode_create(g, p->vals[1]);
                p->type--;
                _ttchild_distribute(p, s);
            } else {
                value = mid;
                goto CASE3;
            }
        }
        if (g->child[0] == p) {
            g->child[1] = s;
        } else {
            g->child[1] = p;
            g->child[2] = s;
        }
        _ttinsert_into_2node(g, mid);//CASE 2
    } else {
CASE3:
        mid = _ttinsert_into_3node(t->root, value);
        p = _ttnode_create(NULL, mid);
        s = _ttnode_create(p, t->root->vals[1]);
        _ttchild_distribute(t->root, s);
        t->root->type--;
        p->child[0] = t->root;
        p->child[2] = s;
        t->root->parent = p;
        t->root = p;
    }
}

static tttree_t *ttcreate(void)
{
    tttree_t *t = malloc(sizeof(ttnode_t));
    t->root = NULL;
    return t;
}

static void _ttfree(ttnode_t *node)
{
    if (node) {
        _ttfree(node->child[0]);
        if (node->type == 2) _ttfree(node->child[1]);
        _ttfree(node->child[2]);
        free(node);
    }
}

static void ttfree(tttree_t *tree)
{
    if (tree) {
        _ttfree(tree->root);
        free(tree);
    }
}

static void _ttprint(const ttnode_t *node, const int tabs)
{
    for (int i = 0; i < tabs; ++i) {
        printf("    ");
    }
    if (node) {
        if (node->type == 1) {
            printf("[%d]\n", node->vals[0]);
            _ttprint(node->child[0], tabs + 1);
        } else {
            printf("[%d,%d]\n", node->vals[0], node->vals[1]);
            _ttprint(node->child[0], tabs + 1);
            _ttprint(node->child[1], tabs + 1);
        }
        _ttprint(node->child[2], tabs + 1);
    } else {
        printf("NULL\n");
    }
}

static void ttprint(const tttree_t *tree)
{
    if (tree) _ttprint(tree->root, 0);
}

static void _ttprint_arr(const ttnode_t *node)
{
    if (node) {
        _ttprint_arr(node->child[0]);
        printf("%d ", node->vals[0]);
        if (node->type == 2) {
            _ttprint_arr(node->child[1]);
            printf("%d ", node->vals[1]);
        }
        _ttprint_arr(node->child[2]);
    }
}

static void ttprint_as_arr(const tttree_t *tree)
{
    printf("{ ");
    if (tree) _ttprint_arr(tree->root);
    printf("}");
}

#define SIZE 1000
/*
int main(void)
{
    tttree_t *tree = ttcreate();

    int *set = rand_set(SIZE);
    print_arr(set, SIZE);

    for (int i = 0; i < SIZE; ++i) {
        ttinsert(tree, set[i]);
    }

//    ttprint(tree);
//    ttprint_as_arr(tree);

    ttfree(tree);
    free(set);
    getchar();
    return 0;
}
*/
void test2(const int *arr, const size_t size)
{
    tttree_t *tree = ttcreate();
    for (int i = 0; i < size; ++i) {
        ttinsert(tree, arr[i]);
    }
    ttfree(tree);
}
