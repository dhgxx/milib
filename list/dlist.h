#ifndef _DLIST_H_
#define _DLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DLNODE_ENT_SIZE 256

typedef struct _dl_node {
  char node[DLNODE_ENT_SIZE];
  struct _dl_node *pre;
  struct _dl_node *next;
  unsigned int deleted;
} dl_node;

typedef struct _dlist {
  dl_node *head;
  dl_node *tail;
  dl_node *cur;
  unsigned int len;
} DLIST;

dl_node *dl_mknode(const char *);
DLIST *dl_init(void);
int dl_empty(DLIST *);
int dl_append(const char *, DLIST *);
int dl_delete(const char *, DLIST *);
void dl_proc(DLIST *, void (*) (const char *));
void dl_free(DLIST *);

#endif /* _DLIST_H_ */
