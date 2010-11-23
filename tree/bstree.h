#ifndef _BSTREE_H_
#define _BSTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BST_ENT_SIZE 256

typedef enum _bst_traverse_order {
  BST_POSTORDER,
  BST_INORDER,
  BST_PREORDER
} BST_TRV_ORDER;

typedef struct _bst_node {
  char node[BST_ENT_SIZE];
  struct _bst_node *left;
  struct _bst_node *right;
  unsigned int deleted;
} bst_node;

typedef struct _bstree {
  bst_node *root;
  unsigned int size;
} BSTREE;

bst_node *bst_mknode(const char *);
BSTREE *bst_init(void);
int bst_empty(BSTREE *);
bst_node *bst_find(const char *, BSTREE *);
int bst_ins(const char *, BSTREE **, const int);
int bst_del(const char *, BSTREE **);

void bst_free(BSTREE **);
void bst_foreach(BSTREE *, BST_TRV_ORDER, void (*) (const bst_node *));

#endif /* _BSTREE_H_ */
