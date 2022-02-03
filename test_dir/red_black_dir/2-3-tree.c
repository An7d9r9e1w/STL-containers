#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int *rand_set(const size_t size);
void print_arr(const int *arr, const size_t size);

static int spaces_g = 0;

static void print_spaces(const int spaces) //TEST
{
    for (int i = 0; i < spaces; ++i)
        printf("  ");
}


typedef struct ttnode_s
{
    struct ttnode_s *parent;
    struct ttnode_s *child[4];
    int vals[2];
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
static void _ttinsert_case2(ttnode_t *p, int value);
static void _ttinsert_case3(tttree_t *t, int value);
static void _ttinsert_case4(tttree_t *t, ttnode_t *p, int value);
static void _ttinsert_case5(tttree_t *t, ttnode_t *p, int value);
static void _ttinsert_case6(tttree_t *t, ttnode_t *p, int value);

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
    int tmp;
    if (value < n->vals[0]) {
        tmp = n->vals[0];
        n->vals[0] = value;
        return tmp;
    } else if (value > n->vals[1]) {
        tmp = n->vals[1];
        n->vals[1] = value;
        return tmp;
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
//    print_spaces(0);//TEST
//    printf("CASE 1 {\n");//TEST
//    spaces_g = 1;
    if (!p)
        t->root = _ttnode_create(NULL, value);
    else if (p->child[0])
        _ttinsert_case5(t, p, value);
    else if (p->type == 1)
        _ttinsert_case2(p, value);
    else if (p->parent) {
        _ttinsert_case4(t, p, value);
    } else
        _ttinsert_case3(t, value);
//    print_spaces(0);//TEST
//    printf("}\n\n");//TEST
//    spaces_g = 0;
}

/*final*/
static void _ttinsert_case2(ttnode_t *p, int value)
{
//    print_spaces(spaces_g++);//TEST
//    printf("CASE 2 {\n");//TEST
    _ttinsert_into_2node(p, value);
//    print_spaces(--spaces_g);//TEST
//    printf("}\n");//TEST
}

/*final*/
static void _ttinsert_case3(tttree_t *t, int value)
{
//    print_spaces(spaces_g++);//TEST
//    printf("CASE 3 {\n");//TEST
    int mid = _ttinsert_into_3node(t->root, value);
//    print_spaces(spaces_g);//TEST
//    printf("mid[%d]\n", mid);//TEST
    ttnode_t *p = _ttnode_create(NULL, mid);
    ttnode_t *s = _ttnode_create(p, t->root->vals[1]);
    _ttchild_distribute(t->root, s);
    t->root->type--;
    p->child[0] = t->root;
    p->child[2] = s;
    t->root->parent = p;
    t->root = p;
//    print_spaces(--spaces_g);//TEST
//    printf("}\n");//TEST
}

static void _ttinsert_case4(tttree_t *t, ttnode_t *p, int value)
{
//    print_spaces(spaces_g++);//TEST
//    printf("CASE 4 {\n");//TEST
    ttnode_t *g = p->parent;
//    print_spaces(spaces_g);//TEST
//    printf("g type = %d\n", g->type + 1);//TEST
    if (g->type == 2) {
        _ttinsert_case6(t, p, value);
        return;
    }
    int mid = _ttinsert_into_3node(p, value);
    ttnode_t *s = _ttnode_create(g, p->vals[1]);
    p->type--;
    _ttchild_distribute(p, s);
/*    print_spaces(spaces_g);//TEST
    printf("g[%p]\n", g);//TEST
    print_spaces(spaces_g);//TEST
    printf("s[%p]\n", s);//TEST
    print_spaces(spaces_g);//TEST
    printf("p[%p]\n", p);//TEST*/
    if (g->child[0] == p) {
        g->child[1] = s;
    } else {
        g->child[1] = p;
        g->child[2] = s;
    }
//    print_spaces(spaces_g);//TEST
//    printf("g type = %d\n", g->type + 1);//TEST
    _ttinsert_case2(g, mid);
//    print_spaces(--spaces_g);//TEST
//    printf("}\n");//TEST
}

static void _ttinsert_case5(tttree_t *t, ttnode_t *p, int value)
{
//    print_spaces(spaces_g++);//TEST
//    printf("CASE 5 {\n");//TEST
    ttnode_t *c;
    if (p->type == 1)
        c = p->child[(value > p->vals[0]) << 1];
    else if (value < p->vals[0])
        c = p->child[0];
    else
        c = p->child[1 + (value > p->vals[1])];

    if (c->child[0])
        _ttinsert_case5(t, c, value);
    else if (c->type == 1)
        _ttinsert_case2(c, value);
    else
        _ttinsert_case4(t, c, value);
//    print_spaces(--spaces_g);//TEST
//    printf("}\n");//TEST
}

static void _ttinsert_case6(tttree_t *t, ttnode_t *p, int value)
{
//    print_spaces(spaces_g++);//TEST
//    printf("CASE 6 {\n");//TEST
    int mid = _ttinsert_into_3node(p, value);
    ttnode_t *g = p->parent;
    ttnode_t *s = _ttnode_create(g, p->vals[1]);
    p->type--;
    _ttchild_distribute(p, s);
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
    if (g->parent)
        _ttinsert_case4(t, g, mid);
    else
        _ttinsert_case3(t, mid);
//    print_spaces(--spaces_g);//TEST
//    printf("}\n");//TEST
}

static void ttinsert(tttree_t *tree, int value)
{
    ttnode_t *p = _ttsearch_border(tree, value);
/*    if (p) {                                                //TEST
        if (p->type == 1)                                   //TEST
            printf("p[%d]\n", p->vals[0]);                //TEST
        else                                                //TEST
            printf("p[%d,%d]\n", p->vals[0], p->vals[1]); //TEST
    } else {                                                //TEST
        printf("p[NULL]\n");                              //TEST
    }                                                       //TEST*/
    _ttinsert_case1(tree, p, value);
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
//        printf("[%d]", node->type + 1);//TEST
/*        if (node->parent) {//TEST
            if (node->parent->type == 1) {//TEST
                printf("[%d]  ", node->parent->vals[0]);//TEST
            } else {//TEST
                printf("[%d,%d]  ", node->parent->vals[0], node->parent->vals[1]);//TEST
            }//TEST
        } else {//TEST
            printf("[NULL]  ");//TEST
        }//TEST*/
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

#define SIZE 100
/*
int main(void)
{
    tttree_t *tree = ttcreate();

    int *set = rand_set(SIZE);
    print_arr(set, SIZE);

    for (int i = 0; i < SIZE; ++i) {
//        printf("TEST %d\t", i);
        ttinsert(tree, set[i]);
//        printf("tree:\n");//TEST
//        ttprint(tree);
    }
//    printf("TEST end\n");

//    ttprint(tree);
    ttprint_as_arr(tree);

    ttfree(tree);
    free(set);
    getchar();
    printf("%zu\n", sizeof(ttnode_t));
    return 0;
}
*/
void test(const int *arr, const size_t size)
{
    tttree_t *tree = ttcreate();
    for (int i = 0; i < size; ++i) {
        ttinsert(tree, arr[i]);
    }
    ttfree(tree);
}
