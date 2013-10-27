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

#ifndef dlist_H_
#define dlist_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef MAXNAMLEN
#define DL_ENTSIZ MAXNAMLEN
#else
#define DL_ENTSIZ 256
#endif

struct dl_node {
  char ent[DL_ENTSIZ];
  struct dl_node *pre;
  struct dl_node *next;
  unsigned int deleted;
};

struct dlist {
  struct dl_node *head;
  struct dl_node *tail;
  struct dl_node *cur;
  unsigned int len;
};

struct dlist *dl_init(void);
int dl_empty(struct dlist *);
int dl_append(const char *, struct dlist *);
int dl_ins_at_pos(const char *, const int, struct dlist *, const int);
int dl_ins_at_val(const char *, const char *, struct dlist *, const int);
struct dl_node *dl_behead(struct dlist *);
void dl_sort(struct dlist *);
int dl_delete(const char *, struct dlist *);
void dl_foreach(struct dlist *, void (*) (struct dl_node *));
void dl_clear(struct dlist *);
void dl_free(struct dlist *);

#endif /* _struct dlist_H_ */
