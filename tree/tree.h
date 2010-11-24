#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TR_ENTSIZ 256

typedef struct _tr_node_t {
  char ent[TR_ENTSIZ];
  struct _tr_node_t *sbl;
  struct _tr_node_t *eld;
  struct _tr_node_t *prt;
  struct _tr_node_t *cld;
} tr_node;

typedef struct _tree {
  tr_node *root;
  tr_node *cur;
  unsigned int size;
} TREE;

tr_node *tr_mknode(const char *);
TREE *tr_init(void);
int tr_empty(TREE **);
void tr_free(TREE **);
tr_node *tr_find(const char *, TREE **);
int tr_add_sbl(const char *, const char *, TREE **);
int tr_add_cld(const char *, const char *, TREE **);
void tr_foreach(TREE **, void (*) (tr_node **));

#endif /* _TREE_H_ */
