
/*
 * Copyright (C) Niklaus F.Schen.
 */

#ifndef __MLN_RBTREE_H
#define __MLN_RBTREE_H
#include "mln_types.h"

typedef struct mln_rbtree_node_s mln_rbtree_node_t;
/*
 * >0 -- the first argument greater than the second.
 * ==0 -- equal.
 * <0 -- less.
 */
typedef int (*rbtree_cmp)(const void *, const void *);
typedef void (*rbtree_free_data)(void *);
typedef int (*rbtree_act)(mln_rbtree_node_t *node, void *rn_data, void *udata);

enum rbtree_color {
    M_RB_RED,
    M_RB_BLACK
};

struct mln_rbtree_attr {
    rbtree_cmp                cmp;
    rbtree_free_data          data_free;
    mln_u32_t                 cache:1;
};

struct mln_rbtree_node_s {
    void                     *data;
    struct mln_rbtree_node_s *prev;
    struct mln_rbtree_node_s *next;
    struct mln_rbtree_node_s *parent;
    struct mln_rbtree_node_s *left;
    struct mln_rbtree_node_s *right;
    enum rbtree_color         color;
};

typedef struct rbtree_s {
    mln_rbtree_node_t         nil;
    mln_rbtree_node_t        *root;
    mln_rbtree_node_t        *min;
    mln_rbtree_node_t        *head;
    mln_rbtree_node_t        *tail;
    mln_rbtree_node_t        *free_head;
    mln_rbtree_node_t        *free_tail;
    mln_rbtree_node_t        *iter;
    rbtree_cmp                cmp;
    rbtree_free_data          data_free;
    mln_uauto_t               nr_node;
    mln_u32_t                 del:1;
    mln_u32_t                 cache:1;
} mln_rbtree_t;

#define mln_rbtree_null(ptr,ptree) ((ptr)==&((ptree)->nil))
extern mln_rbtree_t *
mln_rbtree_init(struct mln_rbtree_attr *attr) __NONNULL1(1);
extern void
mln_rbtree_destroy(mln_rbtree_t *t);
extern void
mln_rbtree_insert(mln_rbtree_t *t, mln_rbtree_node_t *n) __NONNULL2(1,2);
extern void
mln_rbtree_delete(mln_rbtree_t *t, mln_rbtree_node_t *n) __NONNULL2(1,2);
extern mln_rbtree_node_t *
mln_rbtree_successor(mln_rbtree_t *t, mln_rbtree_node_t *n) __NONNULL2(1,2);
extern mln_rbtree_node_t *
mln_rbtree_search(mln_rbtree_t *t, \
                  mln_rbtree_node_t *root, \
                  const void *key) __NONNULL3(1,2,3);
extern mln_rbtree_node_t *
mln_rbtree_min(mln_rbtree_t *t) __NONNULL1(1);

extern mln_rbtree_node_t *
mln_rbtree_node_new(mln_rbtree_t *t, void *data) __NONNULL2(1,2);
extern void 
mln_rbtree_node_free(mln_rbtree_t *t, mln_rbtree_node_t *n) __NONNULL2(1,2);
extern int
mln_rbtree_scan_all(mln_rbtree_t *t, rbtree_act act, void *udata) __NONNULL2(1,2);
#endif

