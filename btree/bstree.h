#ifndef _BSTREE_H_
#define _BSTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BSTNODE_ENT_SIZE 256

typedef struct _bst_node {
  char node[BSTNODE_ENT_SIZE];
  struct _bst_node *left;
  struct _bst_node *right;
} bst_node;

typedef struct _bstree {
  bst_node *root;
} BSTREE;

bst_node *bst_mknode(const char *);
BSTREE *bst_init(void);
int bst_empty(BSTREE *);
bst_node *bst_find(const char *, bst_node *);
void bst_insert(const char *, BSTREE *);
void bst_free(bst_node *);

#endif /* _BSTREE_H_ */
