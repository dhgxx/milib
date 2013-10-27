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

#include <assert.h>

#include "bstree.h"

static struct bst_node *locate(const char *, struct bst_node *);
static int insert(const char *, struct bst_node *, int);
static void foreach(struct bst_node *, enum bst_trv_order, void (*) (struct bst_node *));
static void mem_free(struct bst_node *);

struct bst_node *
bst_mknode(const char *str)
{
  struct bst_node *np;
  
  assert(str != NULL);
  
  if ((np = (struct bst_node *)malloc(sizeof(struct bst_node))) == NULL)
	return (NULL);

  bzero(np->ent, BST_ENTSIZ);
  strlcpy(np->ent, str, BST_ENTSIZ);
  np->left = NULL;
  np->right = NULL;
  np->deleted = 0;
  return (np);
}

struct bstree *
bst_init(void)
{
  struct bstree *tp;
			  
  if (NULL == (tp = (struct bstree *)malloc(sizeof(struct bstree))))
	return (NULL);
  
  tp->root = NULL;
  tp->size = 0;
  return (tp);
}
  
int
bst_empty(struct bstree *tp)
{
  assert(tp != NULL);
  
  if (tp->root == NULL &&
	  tp->size == 0)
	return (1);

  return (0);
}

struct bst_node *
bst_find(const char *str, struct bstree *tp)
{
  assert((str != NULL) &&
		 (tp != NULL) &&
		 !bst_empty(tp));
  
  return (locate(str, tp->root));
}

static struct bst_node *
locate(const char *str, struct bst_node *np)
{
  int m;
  struct bst_node *cur;

  assert((str != NULL) &&
		 (np != NULL));

  cur = np;
  
  if (np->deleted != 1) {
	m = strncmp(str, np->ent, strlen(str) + 1);
	
	if (0 == m)
	  return (np);
	
	if (0 > m) {
	  if (np->left != NULL)
		cur = np = locate(str, np->left);
	  else
		return (np);
	}
	  
	if (0 < m) {
	  if (np->right != NULL)
		cur = np = locate(str, np->right);
	  else
		return (np);
	}
	return (np);
  }
  return (cur);
}

int
bst_ins(const char *str, struct bstree *tp, const int ic)
{
  assert((str != NULL) &&
		 (tp != NULL));
  
  if (bst_empty(tp)) {

	if ((tp->root = bst_mknode(str)) == NULL)
	  return (-1);
	
	tp->size++;
	return (0);
  }
  
  if (0 == insert(str, tp->root, ic)) {
	tp->size++;
	return (0);
  }

  return (-1);
}

static int
insert(const char *str, struct bst_node *pos, const int ic)
{
  int m, ret;
  struct bst_node *np;

  assert((str != NULL) &&
		 (pos != NULL));

  ret = -1;
  np = locate(str, pos);
  m = strncmp(str, np->ent, strlen(str) + 1);

  if (ic == 1 && m == 0) {
	if (np->left == NULL) {
	  if (NULL != (np->left = bst_mknode(str)))
		ret = 0;
	} else {
	  ret = insert(str, np->left, ic);
	}
  }

  if (0 > m) {	  
	if (np->left == NULL) {
	  if (NULL != (np->left = bst_mknode(str)))
		ret = 0;
	} else {
	  ret = insert(str, np->left, ic);
	}
  }
	
  if (0 < m) {	  
	if (np->right == NULL) {
	  if (NULL != (np->right = bst_mknode(str)))
		ret = 0;
	} else {
	  ret = insert(str, np->right, ic);
	}
  }

  return (ret);
}

int
bst_del(const char *str, struct bstree *tp)
{
  struct bst_node *np;

  assert((str != NULL) &&
		 (tp != NULL));
  
  np = locate(str, tp->root);

  if (np != NULL) {
	np->deleted = 1;
	tp->size--;
	return (0);
  }

  return (-1);
}

void
bst_free(struct bstree *tp)
{
  assert(tp != NULL);
   
  mem_free(tp->root);
  if (tp != NULL) {
	free(tp);
	tp = NULL;
  }
}

static void
mem_free(struct bst_node *np)
{
  assert(np != NULL);
  
  if (np->left != NULL)
	mem_free(np->left);
  if (np->right != NULL)
	mem_free(np->right);

  free(np);
  np = NULL;
}

void
bst_foreach(struct bstree *tp, enum bst_trv_order odr, void (*func_p) (struct bst_node *node))
{
  assert((tp != NULL) &&
		 (func_p != NULL));
  
  foreach(tp->root, odr, func_p);
}

static void
foreach(struct bst_node *beg, enum bst_trv_order odr, void (*func_p) (struct bst_node *node))
{
	assert((beg != NULL) &&
		   (func_p != NULL));
	
	switch (odr) {
	case BST_PREORDER:
	  func_p(beg);
	  if (beg->left != NULL)
		foreach(beg->left, BST_PREORDER, func_p);
	  if (beg->right != NULL)
		foreach(beg->right, BST_PREORDER, func_p);
	  break;
	case BST_INORDER:
	  if (beg->left != NULL)
		foreach(beg->left, BST_INORDER, func_p);
	  func_p(beg);
	  if (beg->right != NULL)
		foreach(beg->right, BST_INORDER, func_p);
	  break;
	default:
	case BST_POSTORDER:
	  if (beg->left != NULL)
		foreach(beg->left, BST_POSTORDER, func_p);
	  if (beg->right != NULL)
		foreach(beg->right, BST_POSTORDER, func_p);
	  func_p(beg);
	  break;
	}
}
