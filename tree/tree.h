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

#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef MAXNAMLEN
#define TR_ENTSIZ MAXNAMLEN
#else
#define TR_ENTSIZ 256
#endif

struct tr_node {
  char ent[TR_ENTSIZ];
  struct tr_node *sbl;
  struct tr_node *eld;
  struct tr_node *prt;
  struct tr_node *cld;
};

struct tree {
  struct tr_node *root;
  struct tr_node *cur;
  unsigned int size;
};

struct tr_node *tr_mknode(const char *);
struct tree *tr_init(void);
int tr_empty(struct tree *);
void tr_free(struct tree *);
struct tr_node *tr_find(const char *, struct tree *);
int tr_add_sbl(const char *, const char *, struct tree *);
int tr_add_cld(const char *, const char *, struct tree *);
void tr_foreach(struct tree *, void (*) (struct tr_node *));

#endif /* _TREE_H_ */
