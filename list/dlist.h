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

#ifndef _DLIST_H_
#define _DLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef MAXNAMLEN
#define DL_ENTSIZ MAXNAMLEN
#else
#define DL_ENTSIZ 256
#endif

typedef struct _dl_node {
  char ent[DL_ENTSIZ];
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

DLIST *dl_init(void);
int dl_empty(DLIST *);
int dl_append(const char *, DLIST *);
int dl_ins_at_pos(const char *, const int, DLIST *, const int);
int dl_ins_at_val(const char *, const char *, DLIST *, const int);
dl_node *dl_behead(DLIST *);
void dl_sort(DLIST *);
int dl_delete(const char *, DLIST *);
void dl_foreach(DLIST *, void (*) (dl_node *));
void dl_clear(DLIST *);
void dl_free(DLIST *);

#endif /* _DLIST_H_ */
