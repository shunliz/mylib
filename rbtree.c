#include <stdio.h>   
#include <stdlib.h>   
#include <string.h>   
#include "rbtree.h"   
static void __rb_rotate_left(struct rb_node *node, struct rb_root *root)   
{   
        struct rb_node *right = node->rb_right;   
        struct rb_node *parent = rb_parent(node);   
        if ((node->rb_right = right->rb_left))   
                rb_set_parent(right->rb_left, node);   
        right->rb_left = node;   
        rb_set_parent(right, parent);   
        if (parent) {   
                if (node == parent->rb_left)   
                        parent->rb_left = right;   
                else  
                        parent->rb_right = right;   
        } else  
                root->rb_node = right;   
        rb_set_parent(node, right);   
}   
static void __rb_rotate_right(struct rb_node *node, struct rb_root *root)   
{   
        struct rb_node *left = node->rb_left;   
        struct rb_node *parent = rb_parent(node);   
        if ((node->rb_left = left->rb_right))   
                rb_set_parent(left->rb_right, node);   
        left->rb_right = node;   
        rb_set_parent(left, parent);   
        if (parent) {   
                if (node == parent->rb_right)   
                        parent->rb_right = left;   
                else  
                        parent->rb_left = left;   
        } else  
                root->rb_node = left;   
        rb_set_parent(node, left);   
}   
void rb_insert_color(struct rb_node *node, struct rb_root *root)   
{   
    struct rb_node *parent, *gparent;   
    while ((parent = rb_parent(node)) && rb_is_red(parent)) {   
        gparent = rb_parent(parent);   
        if (parent == gparent->rb_left)  { // node is left child of parent   
            {   
                struct rb_node *uncle = gparent->rb_right;   
                if (uncle && rb_is_red(uncle)) { // case 1   
                    rb_set_black(uncle);   
                    rb_set_black(parent);   
                    rb_set_red(gparent);   
                    node = gparent;   
                    continue;   
                }   
            }   
            if (parent->rb_right == node) { // case 2   
                struct rb_node *tmp;   
                __rb_rotate_left(parent, root);   
                tmp = parent;   
                parent = node;   
                node = tmp;   
            }   
            // case 3   
            rb_set_black(parent);   
            rb_set_red(gparent);   
            __rb_rotate_right(gparent, root);   
        } else { // node is right child of parent   
            {   
                struct rb_node *uncle = gparent->rb_left;   
                if (uncle && rb_is_red(uncle)) { // case 1   
                    rb_set_black(uncle);   
                    rb_set_black(parent);   
                    rb_set_red(gparent);   
                    node = gparent;   
                    continue;   
                }   
            }   
            if (parent->rb_left == node) { // case 2   
                struct rb_node *tmp;   
                __rb_rotate_right(parent, root);   
                tmp = parent;   
                parent = node;   
                node = tmp;   
            }   
            // case 3   
            rb_set_black(parent);   
            rb_set_red(gparent);   
            __rb_rotate_left(gparent, root);   
        }   
    }   
    rb_set_black(root->rb_node);   
}   
static int rb_compare(struct rb_key key1, struct rb_key key2)   
{   
    return (key1.key - key2.key);   
}   
struct rb_node* rb_newnode(struct rb_key *rb_key)   
{   
    struct rb_node *node = (struct rb_node *)malloc(sizeof(struct rb_node));   
    if (node) {   
        node->rb_parent = NULL;   
        node->rb_left = NULL;   
        node->rb_right = NULL;   
        node->rb_color = RB_RED;   
        memcpy(&node->rb_key, rb_key, sizeof(struct rb_key));   
    }   
    return node;   
}   
void rb_insert(struct rb_node *node, struct rb_root *root)   
{   
    struct rb_node *p = root->rb_node;   
    struct rb_node *q = NULL;   
    while (p != NULL) {   
        q = p;   
        if (rb_compare(node->rb_key, p->rb_key) < 0)   
            p = p->rb_left;   
        else  
            p = p->rb_right;   
    }   
    node->rb_parent = q;   
    if (q == NULL) {   
        root->rb_node = node;   
    } else {   
        if (rb_compare(node->rb_key, q->rb_key) < 0)   
            q->rb_left = node;   
        else  
            q->rb_right = node;   
    }   
    rb_insert_color(node, root);   
}   
static void __rb_erase_color(struct rb_node *node, struct rb_node *parent, struct rb_root *root)   
{   
    struct rb_node *other;   
    while ((!node || rb_is_black(node)) && node != root->rb_node)   
    {   
        if (parent->rb_left == node)   
        {   
            other = parent->rb_right;   
            // case 1   
            if (rb_is_red(other))   
            {   
                rb_set_black(other);   
                rb_set_red(parent);   
                __rb_rotate_left(parent, root);   
                other = parent->rb_right;   
            }   
            // case 2   
            if ((!other->rb_left || rb_is_black(other->rb_left)) &&   
                (!other->rb_right || rb_is_black(other->rb_right)))   
            {   
                rb_set_red(other);   
                node = parent;   
                parent = rb_parent(node);   
            }   
            else  
            {   
                // case 3   
                if (!other->rb_right || rb_is_black(other->rb_right))   
                {   
                    struct rb_node *o_left;   
                    if ((o_left = other->rb_left))   
                        rb_set_black(o_left);   
                    rb_set_red(other);   
                    __rb_rotate_right(other, root);   
                    other = parent->rb_right;   
                }   
                // case 4   
                rb_set_color(other, rb_color(parent));   
                rb_set_black(parent);   
                if (other->rb_right)   
                    rb_set_black(other->rb_right);   
                __rb_rotate_left(parent, root);   
                node = root->rb_node;   
                break;   
            }   
        }   
        else  
        {   
            other = parent->rb_left;   
            // case 1   
            if (rb_is_red(other))   
            {   
                rb_set_black(other);   
                rb_set_red(parent);   
                __rb_rotate_right(parent, root);   
                other = parent->rb_left;   
            }   
            // case 2   
            if ((!other->rb_left || rb_is_black(other->rb_left)) &&   
                (!other->rb_right || rb_is_black(other->rb_right)))   
            {   
                rb_set_red(other);   
                node = parent;   
                parent = rb_parent(node);   
            }   
            else  
            {   
                // case 3   
                if (!other->rb_left || rb_is_black(other->rb_left))   
                {   
                    register struct rb_node *o_right;   
                    if ((o_right = other->rb_right))   
                        rb_set_black(o_right);   
                    rb_set_red(other);   
                    __rb_rotate_left(other, root);   
                    other = parent->rb_left;   
                }   
                // case 4   
                rb_set_color(other, rb_color(parent));   
                rb_set_black(parent);   
                if (other->rb_left)   
                    rb_set_black(other->rb_left);   
                __rb_rotate_right(parent, root);   
                node = root->rb_node;   
                break;   
            }   
        }   
    }   
    if (node)   
        rb_set_black(node);   
}   
void rb_erase(struct rb_node *node, struct rb_root *root)   
{   
    struct rb_node *child, *parent;   
    int color;   
    if (!node->rb_left)   
        child = node->rb_right;   
    else if (!node->rb_right)   
        child = node->rb_left;   
    else  
    {   
        struct rb_node *old = node, *left;   
        node = node->rb_right;   
        while ((left = node->rb_left) != NULL)   
            node = left;   
        child = node->rb_right;   
        parent = rb_parent(node);   
        color = rb_color(node);   
        if (child)   
            rb_set_parent(child, parent);   
        if (parent == old) {   
            parent->rb_right = child;   
            parent = node;   
        } else  
            parent->rb_left = child;   
        node->rb_color = old->rb_color;   
        node->rb_parent = old->rb_parent;   
        node->rb_right = old->rb_right;   
        node->rb_left = old->rb_left;   
        if (rb_parent(old))   
        {   
            if (rb_parent(old)->rb_left == old)   
                rb_parent(old)->rb_left = node;   
            else  
                rb_parent(old)->rb_right = node;   
        } else  
            root->rb_node = node;   
        rb_set_parent(old->rb_left, node);   
        if (old->rb_right)   
            rb_set_parent(old->rb_right, node);   
        goto color;   
    }   
    parent = rb_parent(node);   
    color = rb_color(node);   
    if (child)   
        rb_set_parent(child, parent);   
    if (parent)   
    {   
        if (parent->rb_left == node)   
            parent->rb_left = child;   
        else  
            parent->rb_right = child;   
    }   
    else  
        root->rb_node = child;   
 color:   
    if (color == RB_BLACK)   
        __rb_erase_color(child, parent, root);   
}   
struct rb_node *rb_first(struct rb_root *root)   
{   
    struct rb_node  *n;   
    n = root->rb_node;   
    if (!n)   
        return NULL;   
    while (n->rb_left)   
        n = n->rb_left;   
    return n;   
}   
struct rb_node *rb_last(struct rb_root *root)   
{   
    struct rb_node  *n;   
    n = root->rb_node;   
    if (!n)   
        return NULL;   
    while (n->rb_right)   
        n = n->rb_right;   
    return n;   
}   
struct rb_node *rb_next(struct rb_node *node)   
{   
    struct rb_node *parent;   
    if (rb_parent(node) == node)   
        return NULL;   
    /* If we have a right-hand child, go down and then left as far  
       as we can. */  
    if (node->rb_right) {   
        node = node->rb_right;    
        while (node->rb_left)   
            node=node->rb_left;   
        return node;   
    }   
    /* No right-hand children.  Everything down and left is  
       smaller than us, so any 'next' node must be in the general  
       direction of our parent. Go up the tree; any time the  
       ancestor is a right-hand child of its parent, keep going  
       up. First time it's a left-hand child of its parent, said  
       parent is our 'next' node. */  
    while ((parent = rb_parent(node)) && node == parent->rb_right)   
        node = parent;   
    return parent;   
}   
struct rb_node *rb_prev(struct rb_node *node)   
{   
    struct rb_node *parent;   
    if (rb_parent(node) == node)   
        return NULL;   
    /* If we have a left-hand child, go down and then right as far  
       as we can. */  
    if (node->rb_left) {   
        node = node->rb_left;    
        while (node->rb_right)   
            node=node->rb_right;   
        return node;   
    }   
    /* No left-hand children. Go up till we find an ancestor which  
       is a right-hand child of its parent */  
    while ((parent = rb_parent(node)) && node == parent->rb_left)   
        node = parent;   
    return parent;   
}   
void rb_replace_node(struct rb_node *victim, struct rb_node *new_node, struct rb_root *root)   
{   
    struct rb_node *parent = rb_parent(victim);   
    /* Set the surrounding nodes to point to the replacement */  
    if (parent) {   
        if (victim == parent->rb_left)   
            parent->rb_left = new_node;   
        else  
            parent->rb_right = new_node;   
    } else {   
        root->rb_node = new_node;   
    }   
    if (victim->rb_left)   
        rb_set_parent(victim->rb_left, new_node);   
    if (victim->rb_right)   
        rb_set_parent(victim->rb_right, new_node);   
    /* Copy the pointers/colour from the victim to the replacement */  
    *new_node = *victim;   
}   
struct rb_node *rb_search(struct rb_root *root, struct rb_key key)   
{   
    struct rb_node *p = root->rb_node;   
    while(p != NULL && rb_compare(p->rb_key, key) != 0) {   
        p = (rb_compare(p->rb_key, key) > 0) ? p->rb_left : p->rb_right;   
    }   
    return p;   
}   
void rb_traverse(struct rb_node *p)   
{   
    if (p) {   
        if (p->rb_left)   
            rb_traverse(p->rb_left);   
        printf(" %d ", p->rb_key.key);   
        if (p->rb_right)   
            rb_traverse(p->rb_right);   
    }   
}  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbtree.h"
static void __rb_rotate_left(struct rb_node *node, struct rb_root *root)
{
        struct rb_node *right = node->rb_right;
        struct rb_node *parent = rb_parent(node);
        if ((node->rb_right = right->rb_left))
                rb_set_parent(right->rb_left, node);
        right->rb_left = node;
        rb_set_parent(right, parent);
        if (parent) {
                if (node == parent->rb_left)
                        parent->rb_left = right;
                else
                        parent->rb_right = right;
        } else
                root->rb_node = right;
        rb_set_parent(node, right);
}
static void __rb_rotate_right(struct rb_node *node, struct rb_root *root)
{
        struct rb_node *left = node->rb_left;
        struct rb_node *parent = rb_parent(node);
        if ((node->rb_left = left->rb_right))
                rb_set_parent(left->rb_right, node);
        left->rb_right = node;
        rb_set_parent(left, parent);
        if (parent) {
                if (node == parent->rb_right)
                        parent->rb_right = left;
                else
                        parent->rb_left = left;
        } else
                root->rb_node = left;
        rb_set_parent(node, left);
}
void rb_insert_color(struct rb_node *node, struct rb_root *root)
{
	struct rb_node *parent, *gparent;
	while ((parent = rb_parent(node)) && rb_is_red(parent))	{
		gparent = rb_parent(parent);
		if (parent == gparent->rb_left)	{ // node is left child of parent
			{
				struct rb_node *uncle = gparent->rb_right;
				if (uncle && rb_is_red(uncle)) { // case 1
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}
			if (parent->rb_right == node) { // case 2
				struct rb_node *tmp;
				__rb_rotate_left(parent, root);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			// case 3
			rb_set_black(parent);
			rb_set_red(gparent);
			__rb_rotate_right(gparent, root);
		} else { // node is right child of parent
			{
				struct rb_node *uncle = gparent->rb_left;
				if (uncle && rb_is_red(uncle)) { // case 1
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}
			if (parent->rb_left == node) { // case 2
				struct rb_node *tmp;
				__rb_rotate_right(parent, root);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			// case 3
			rb_set_black(parent);
			rb_set_red(gparent);
			__rb_rotate_left(gparent, root);
		}
	}
	rb_set_black(root->rb_node);
}
static int rb_compare(struct rb_key key1, struct rb_key key2)
{
	return (key1.key - key2.key);
}
struct rb_node* rb_newnode(struct rb_key *rb_key)
{
	struct rb_node *node = (struct rb_node *)malloc(sizeof(struct rb_node));
	if (node) {
		node->rb_parent = NULL;
		node->rb_left = NULL;
		node->rb_right = NULL;
		node->rb_color = RB_RED;
		memcpy(&node->rb_key, rb_key, sizeof(struct rb_key));
	}
	return node;
}
void rb_insert(struct rb_node *node, struct rb_root *root)
{
	struct rb_node *p = root->rb_node;
	struct rb_node *q = NULL;
	while (p != NULL) {
		q = p;
		if (rb_compare(node->rb_key, p->rb_key) < 0)
			p = p->rb_left;
		else
			p = p->rb_right;
	}
	node->rb_parent = q;
	if (q == NULL) {
		root->rb_node = node;
	} else {
		if (rb_compare(node->rb_key, q->rb_key) < 0)
			q->rb_left = node;
		else
			q->rb_right = node;
	}
	rb_insert_color(node, root);
}
static void __rb_erase_color(struct rb_node *node, struct rb_node *parent, struct rb_root *root)
{
	struct rb_node *other;
	while ((!node || rb_is_black(node)) && node != root->rb_node)
	{
		if (parent->rb_left == node)
		{
			other = parent->rb_right;
			// case 1
			if (rb_is_red(other))
			{
				rb_set_black(other);
				rb_set_red(parent);
				__rb_rotate_left(parent, root);
				other = parent->rb_right;
			}
			// case 2
			if ((!other->rb_left || rb_is_black(other->rb_left)) &&
			    (!other->rb_right || rb_is_black(other->rb_right)))
			{
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				// case 3
				if (!other->rb_right || rb_is_black(other->rb_right))
				{
					struct rb_node *o_left;
					if ((o_left = other->rb_left))
						rb_set_black(o_left);
					rb_set_red(other);
					__rb_rotate_right(other, root);
					other = parent->rb_right;
				}
				// case 4
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				if (other->rb_right)
					rb_set_black(other->rb_right);
				__rb_rotate_left(parent, root);
				node = root->rb_node;
				break;
			}
		}
		else
		{
			other = parent->rb_left;
			// case 1
			if (rb_is_red(other))
			{
				rb_set_black(other);
				rb_set_red(parent);
				__rb_rotate_right(parent, root);
				other = parent->rb_left;
			}
			// case 2
			if ((!other->rb_left || rb_is_black(other->rb_left)) &&
			    (!other->rb_right || rb_is_black(other->rb_right)))
			{
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				// case 3
				if (!other->rb_left || rb_is_black(other->rb_left))
				{
					register struct rb_node *o_right;
					if ((o_right = other->rb_right))
						rb_set_black(o_right);
					rb_set_red(other);
					__rb_rotate_left(other, root);
					other = parent->rb_left;
				}
				// case 4
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				if (other->rb_left)
					rb_set_black(other->rb_left);
				__rb_rotate_right(parent, root);
				node = root->rb_node;
				break;
			}
		}
	}
	if (node)
		rb_set_black(node);
}
void rb_erase(struct rb_node *node, struct rb_root *root)
{
	struct rb_node *child, *parent;
	int color;
	if (!node->rb_left)
		child = node->rb_right;
	else if (!node->rb_right)
		child = node->rb_left;
	else
	{
		struct rb_node *old = node, *left;
		node = node->rb_right;
		while ((left = node->rb_left) != NULL)
			node = left;
		child = node->rb_right;
		parent = rb_parent(node);
		color = rb_color(node);
		if (child)
			rb_set_parent(child, parent);
		if (parent == old) {
			parent->rb_right = child;
			parent = node;
		} else
			parent->rb_left = child;
		node->rb_color = old->rb_color;
		node->rb_parent = old->rb_parent;
		node->rb_right = old->rb_right;
		node->rb_left = old->rb_left;
		if (rb_parent(old))
		{
			if (rb_parent(old)->rb_left == old)
				rb_parent(old)->rb_left = node;
			else
				rb_parent(old)->rb_right = node;
		} else
			root->rb_node = node;
		rb_set_parent(old->rb_left, node);
		if (old->rb_right)
			rb_set_parent(old->rb_right, node);
		goto color;
	}
	parent = rb_parent(node);
	color = rb_color(node);
	if (child)
		rb_set_parent(child, parent);
	if (parent)
	{
		if (parent->rb_left == node)
			parent->rb_left = child;
		else
			parent->rb_right = child;
	}
	else
		root->rb_node = child;
 color:
	if (color == RB_BLACK)
		__rb_erase_color(child, parent, root);
}
struct rb_node *rb_first(struct rb_root *root)
{
	struct rb_node	*n;
	n = root->rb_node;
	if (!n)
		return NULL;
	while (n->rb_left)
		n = n->rb_left;
	return n;
}
struct rb_node *rb_last(struct rb_root *root)
{
	struct rb_node	*n;
	n = root->rb_node;
	if (!n)
		return NULL;
	while (n->rb_right)
		n = n->rb_right;
	return n;
}
struct rb_node *rb_next(struct rb_node *node)
{
	struct rb_node *parent;
	if (rb_parent(node) == node)
		return NULL;
	/* If we have a right-hand child, go down and then left as far
	   as we can. */
	if (node->rb_right) {
		node = node->rb_right; 
		while (node->rb_left)
			node=node->rb_left;
		return node;
	}
	/* No right-hand children.  Everything down and left is
	   smaller than us, so any 'next' node must be in the general
	   direction of our parent. Go up the tree; any time the
	   ancestor is a right-hand child of its parent, keep going
	   up. First time it's a left-hand child of its parent, said
	   parent is our 'next' node. */
	while ((parent = rb_parent(node)) && node == parent->rb_right)
		node = parent;
	return parent;
}
struct rb_node *rb_prev(struct rb_node *node)
{
	struct rb_node *parent;
	if (rb_parent(node) == node)
		return NULL;
	/* If we have a left-hand child, go down and then right as far
	   as we can. */
	if (node->rb_left) {
		node = node->rb_left; 
		while (node->rb_right)
			node=node->rb_right;
		return node;
	}
	/* No left-hand children. Go up till we find an ancestor which
	   is a right-hand child of its parent */
	while ((parent = rb_parent(node)) && node == parent->rb_left)
		node = parent;
	return parent;
}
void rb_replace_node(struct rb_node *victim, struct rb_node *new_node, struct rb_root *root)
{
	struct rb_node *parent = rb_parent(victim);
	/* Set the surrounding nodes to point to the replacement */
	if (parent) {
		if (victim == parent->rb_left)
			parent->rb_left = new_node;
		else
			parent->rb_right = new_node;
	} else {
		root->rb_node = new_node;
	}
	if (victim->rb_left)
		rb_set_parent(victim->rb_left, new_node);
	if (victim->rb_right)
		rb_set_parent(victim->rb_right, new_node);
	/* Copy the pointers/colour from the victim to the replacement */
	*new_node = *victim;
}
struct rb_node *rb_search(struct rb_root *root, struct rb_key key)
{
	struct rb_node *p = root->rb_node;
	while(p != NULL && rb_compare(p->rb_key, key) != 0) {
		p = (rb_compare(p->rb_key, key) > 0) ? p->rb_left : p->rb_right;
	}
	return p;
}
void rb_traverse(struct rb_node *p)
{
	if (p) {
		if (p->rb_left)
			rb_traverse(p->rb_left);
		printf(" %d ", p->rb_key.key);
		if (p->rb_right)
			rb_traverse(p->rb_right);
	}
}
 

demo.c

view plaincopy to clipboardprint?
#include <stdio.h>  
#include <stdlib.h>  
#include "rbtree.h"   
int main(int argc, char *argv[])   
{   
    int i;   
    struct rb_root root;   
    root.rb_node = NULL;   
    for (i = 2; i < argc; i++ ) {   
        struct rb_key rb_key;   
        rb_key.key = atol(argv[i]);   
        struct rb_node *node = rb_newnode(&rb_key);   
        if (node) {   
            rb_insert(node, &root);   
        }   
    }   
    rb_traverse(root.rb_node);   
    printf("\n");   
    struct rb_key rb_key;   
    rb_key.key = atol(argv[1]);   
    struct rb_node *node = rb_search(&root, rb_key);   
    if (node) {   
        printf("key = %d\n", node->rb_key.key);   
        rb_erase(node, &root);   
        rb_traverse(root.rb_node);   
        printf("\n");   
    } else {   
        printf("%d is not found\n", rb_key.key);   
    }   
    return 0;   
}