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

#include "tree.h"

static void foreach(tr_node **, void (*) (tr_node **));
static tr_node *locate(const char *, tr_node **);
static void mem_free(tr_node **);

tr_node *
tr_mknode(const char *str)
{
  tr_node *np;
  
  if (str == NULL)
	return (NULL);

  np = (tr_node *)malloc(sizeof(tr_node));

  if (np != NULL) {
	bzero(np->ent, TR_ENTSIZ);
	strlcpy(np->ent, str, TR_ENTSIZ);
	np->sbl = NULL;
	np->eld = NULL;
	np->prt = NULL;
	np->cld = NULL;
  }

  return (np);
}

TREE *
tr_init(void)
{
  TREE *tp;

  tp = (TREE *)malloc(sizeof(TREE));

  if (tp != NULL) {
	tp->root = NULL;
	tp->size = 0;
  }

  return (tp);
}

int
tr_empty(TREE **t)
{
  TREE *tp = *t;
  
  if (tp == NULL)
	return (1);

  if (tp->root == NULL &&
	  tp->size == 0)
	return (1);

  return (0);
}

void
tr_free(TREE **tp)
{
  TREE *p;

  p = *tp;

  if (p == NULL)
	return;
  if (tr_empty(&p)) {
	free(p);
	p = NULL;
	return;
  }

  if (p->root != NULL)
	mem_free(&(p->root));

  if (p != NULL) {
	free(p);
	p = NULL;
  }
}

tr_node *
tr_find(const char *str, TREE **t)
{
  tr_node *np;
  TREE *tp = *t;
  
  if (str == NULL)
	return (NULL);
  if (tp == NULL)
	return (NULL);
  if (tr_empty(&tp))
	return (NULL);

  return (np = locate(str, &(tp->root)));
}

void
tr_foreach(TREE **t, void (*func_p)(tr_node **np))
{
  TREE *tp = *t;
  
  if (tp == NULL)
	return;
  if (func_p == NULL)
	return;
  if (tr_empty(&tp))
	return;

  foreach(&(tp->root), func_p);
}

static void
foreach(tr_node **n, void (*func_p) (tr_node **node))
{
  tr_node *np = *n;
  
  if (np == NULL)
	return;
  if (func_p == NULL)
	return;

  func_p(&np);

  if (np->sbl != NULL)
	foreach(&(np->sbl), func_p);
  if (np->cld != NULL)
	foreach(&(np->cld), func_p);
}

static tr_node *
locate(const char *str, tr_node **n)
{
  tr_node *np = *n;
  
  if (str == NULL)
	return (NULL);
  if (np == NULL)
	return (NULL);
  if (np->ent == NULL)
	return (NULL);
  
  if (0 == strncmp(str, np->ent, strlen(str) + 1))
	return (np);

  if (np->sbl != NULL)
	np = locate(str, &(np->sbl));
  if (np->cld != NULL)
	np = locate(str, &(np->cld));

  return (np);
}

int
tr_add_sbl(const char *str, const char *src, TREE **t)
{
  tr_node *np;
  TREE *tp = *t;
  
  if (str == NULL)
	return (-1);
  if (src == NULL)
	return (-1);
  if (tp == NULL)
	return (-1);
  
  if (tr_empty(&tp)) {
	tp->cur = tp->root = tr_mknode(str);
	tp->size++;
	return (0);
  }

  if (NULL == (np = locate(src, &(tp->root))))
	return (-1);

  while (np->sbl != NULL)
	np = np->sbl;

  tp->cur = np->sbl = tr_mknode(str);
  np->sbl->eld = np;
  tp->size++;
  return (0);
}

int
tr_add_cld(const char *str, const char *src, TREE **t)
{
  tr_node *np;
  TREE *tp = *t;

  if (str == NULL)
	return (-1);
  if (src == NULL)
	return (-1);
  if (tp == NULL)
	return (-1);

  if (tr_empty(&tp)) {
	tp->cur = tp->root = tr_mknode(str);
	tp->size++;
	return (0);
  }

  if (NULL == (np = locate(src, &(tp->root))))
	return (-1);

  if (np->cld == NULL) {  
	tp->cur = np->cld = tr_mknode(str);
	np->cld->prt = np;
	tp->size++;
	return (0);
  }

  np = np->cld;
  while (np->sbl != NULL)
	np = np->sbl;

  tp->cur = np->sbl = tr_mknode(str);
  np->sbl->eld = np;
  tp->size++;
  return (0);
}
  
static void
mem_free(tr_node **np)
{
  tr_node *p;

  p = *np;

  if (p == NULL)
	return;
  
  if (p->cld != NULL)
	mem_free(&(p->cld));
  if (p->sbl != NULL)
	mem_free(&(p->sbl));
  
  if (p->cld == NULL &&
	  p->sbl == NULL) {
	free(p);
	p = NULL;
	return;
  }
}
