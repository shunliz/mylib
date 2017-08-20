#ifndef _RBTREE_H   
#define _RBTREE_H   
#include <stdio.h>   
#define RB_RED      0   
#define RB_BLACK    1   
struct rb_key {   
    int key;   
};   
struct rb_node {   
    struct rb_node *rb_parent;   
    struct rb_node *rb_right;   
    struct rb_node *rb_left;   
    struct rb_key rb_key;   
    int rb_color;   
};   
struct rb_root {   
        struct rb_node *rb_node;   
};   
#define rb_parent(r)   ((struct rb_node *)((r)->rb_parent))   
#define rb_color(r)   ((r)->rb_color)   
#define rb_is_red(r)   (!rb_color(r))   
#define rb_is_black(r) rb_color(r)   
#define rb_set_red(r)  do { (r)->rb_color = RB_RED; } while (0)   
#define rb_set_black(r)  do { (r)->rb_color = RB_BLACK; } while (0)   
static inline void rb_set_parent(struct rb_node *rb, struct rb_node *p)   
{   
    rb->rb_parent = p;   
}   
static inline void rb_set_color(struct rb_node *rb, int color)   
{   
        rb->rb_color = color;   
}   
#define RB_ROOT (struct rb_root) { NULL, }   
#define RB_EMPTY_ROOT(root)     ((root)->rb_node == NULL)   
#define RB_EMPTY_NODE(node)     (rb_parent(node) == node)   
#define RB_CLEAR_NODE(node)     (rb_set_parent(node, node))   
extern void rb_insert_color(struct rb_node *, struct rb_root *);   
extern void rb_erase(struct rb_node *, struct rb_root *);   
extern void rb_insert(struct rb_node *, struct rb_root *);   
extern void rb_traverse(struct rb_node *);   
extern struct rb_node *rb_newnode(struct rb_key *);   
extern struct rb_node *rb_search(struct rb_root *, struct rb_key);   
/* Find logical next and previous nodes in a tree */  
extern struct rb_node *rb_next(struct rb_node *);   
extern struct rb_node *rb_prev(struct rb_node *);   
extern struct rb_node *rb_first(struct rb_root *);   
extern struct rb_node *rb_last(struct rb_root *);   
/* Fast replacement of a single node without remove/rebalance/add/rebalance */  
extern void rb_replace_node(struct rb_node *victim, struct rb_node *new_node,   
                            struct rb_root *root);   
static inline void rb_link_node(struct rb_node * node, struct rb_node * parent,   
                                struct rb_node ** rb_link)   
{   
        node->rb_parent = parent;   
        node->rb_left = node->rb_right = NULL;   
        *rb_link = node;   
}   
#endif