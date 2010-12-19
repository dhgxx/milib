/*
 * Copyright (c) 2005-2010 Denise H. G. <darcsis@gmail.com>
 * All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#ifndef _BSTREE_H_
#define _BSTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BST_ENTSIZ 256

typedef enum _bst_traverse_order {
  BST_POSTORDER,
  BST_INORDER,
  BST_PREORDER
} BST_TRV_ORDER;

typedef struct _bst_node {
  char ent[BST_ENTSIZ];
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
int bst_ins(const char *, BSTREE *, const int);
int bst_del(const char *, BSTREE *);

void bst_free(BSTREE *);
void bst_foreach(BSTREE *, BST_TRV_ORDER, void (*) (bst_node *));

#endif /* _BSTREE_H_ */
