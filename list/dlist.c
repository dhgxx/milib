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

#include "dlist.h"

static void ins_after(dl_node *, dl_node *);
static void ins_before(dl_node *, dl_node *);
static int swap(dl_node *, dl_node *);

dl_node *
dl_mknode(const char *str)
{
  dl_node *np;
  
  if (str == NULL)
	return (NULL);
  
  if ((np = (dl_node *)malloc(sizeof(dl_node))) == NULL)
	return (NULL);
  
  bzero(np->ent, DL_ENTSIZ);
  strlcpy(np->ent, str, DL_ENTSIZ);
  np->deleted = 0;
  np->pre = NULL;
  np->next = NULL;
  return (np);
}

DLIST *
dl_init(void)
{
  DLIST *dl;
  
  if ((dl = (DLIST *)malloc(sizeof(DLIST))) == NULL)
	return (NULL);
  
  dl->head = NULL;
  dl->tail = NULL;
  dl->cur = NULL;
  dl->len = 0;
  return (dl);
}

int
dl_empty(DLIST *dlp)
{  
  if (dlp == NULL)
	return (1);

  if ((dlp->head == NULL) &&
	  (dlp->tail == NULL) &&
	  (dlp->cur == NULL) &&
	  (dlp->len == 0)) {
	return (1);
  }

  return (0);
}

int
dl_append(const char *str, DLIST *dlp)
{
  dl_node *new;
  
  if (dlp == NULL)
	return (-1);

  new = dl_mknode(str);

  if (dl_empty(dlp)) {
	dlp->head = new;
  } else {
	dlp->tail->next = new;
	new->pre = dlp->tail;
  }
	
  dlp->cur = new;
  dlp->tail = new;
  dlp->len++;
  return (0);
}

static void
ins_after(dl_node *src, dl_node *dst)
{
  assert((src != NULL) &&
		 (dst != NULL));
  
  dst->pre = src;
  dst->next = src->next;
  if (src->next != NULL)
	src->next->pre = dst;
  src->next = dst;
}

static void
ins_before(dl_node *src, dl_node *dst)
{
  assert((src != NULL) &&
		 (dst != NULL));
  
  dst->next = src;
  if (src->pre != NULL) {	
	dst->pre = src->pre;
	src->pre->next = dst;
  }
  src->pre = dst;
}

static int
swap(dl_node *front, dl_node *rear)
{
  dl_node *fp, *rn;
  
  assert((front != NULL) &&
		 (rear != NULL));

  /* simple: we have only two nodes */
  /* to deal with. */
  if (front->pre == NULL &&
	  rear->next == NULL) {
	front->next = NULL;
	front->pre = rear;
	rear->pre = NULL;
	rear->next = front;
	return (0);
  }

  /* we are at the head. */
  if (front->pre == NULL &&
	  rear->next != NULL) {
	rn = rear->next;

	front->next = rn;
	front->pre = rear;
	rear->next = front;
	rear->pre = NULL;
	rn->pre = front;
	return (0);
  }

  /* we are at the tail. */
  if (front->pre != NULL &&
	  rear->next == NULL) {
	fp = front->pre;

	fp->next = rear;
	front->next = NULL;
	front->pre = rear;
	rear->next = front;
	rear->pre = fp;
	return (0);
  }

  /* hard: the two nodes to swap */
  /* have neighbors. */
  if (front->pre != NULL &&
	  rear->next != NULL) {
	fp = front->pre;
	rn = rear->next;

	rear->pre = fp;
	front->pre = rear;
	rn->pre = front;

	rear->next = front;
	front->next = rn;
	fp->next = rear;
	return (0);
  }
  /* should never reach here! */
  return (-1);
}

int
dl_ins_at_pos(const char *str, int pos, DLIST *dlp, const int before)
{
  int i;
  dl_node *new, *np;
  
  assert((str != NULL) &&
		 (dlp != NULL));
	
  new = dl_mknode(str);
	
  if (dl_empty(dlp)) {
	dlp->cur = dlp->head = dlp->tail = new;
	dlp->len++;
  } else {
	dlp->cur = new;
	if (pos <= 0) {
	  new->next = dlp->head;
	  dlp->head->pre = new;
	  dlp->head = new;
	  dlp->len++;
	}

	if (pos > 0 && pos < dlp->len) {
	  np = dlp->head;
	  for (i = 0; i < pos && np; i++)
		np = np->next;

	  if (before == 1)
		ins_before(np, new);
	  else
		ins_after(np, new);
	  
	  dlp->len++;
	}

	if (pos >= dlp->len) {
	  new->pre = dlp->tail->pre;
	  dlp->tail->next = new;
	  dlp->tail = new;
	  dlp->len++;
	}
  }

  return (0);
}

int
dl_ins_at_val(const char *str, const char *pos, DLIST *dlp, const int before)
{
  dl_node *new, *np;
  
  assert((str != NULL) &&
		 (pos != NULL) &&
		 (dlp != NULL));

  dlp->cur = new = dl_mknode(str);
	
  if (dl_empty(dlp)) {
	dlp->head = dlp->tail = new;
	dlp->len++;
  } else {
	np = dlp->head;
	while (np) {
	  if (0 == strncmp(pos, np->ent, strlen(pos) + 1)) {
		if (before == 1) {
		  ins_before(np, new);
		  if (np == dlp->head)
			dlp->head = new;
		} else {
		  ins_after(np, new);
		  if (np == dlp->tail)
			dlp->tail = new;
		}
		
		dlp->len++;
		break;
	  }
	  np = np->next;
	}
  }
  return (0);
}

void
dl_sort(DLIST *dlp)
{
  int m, ret;
  char *pre, *next;
  dl_node *front, *rear;
  
  assert((dlp != NULL));

  if (dl_empty(dlp))
	return;

  if (dlp->tail == dlp->head &&
	  dlp->len == 1)
	return;

  rear = dlp->tail;
  front = rear->pre;
  dlp->cur = front;

  while (dlp->cur != NULL) {

	pre = front->ent;
	next = rear->ent;

	if (pre != NULL && next != NULL)
	  m = strncmp(pre, next, strlen(next) + 1);
	else
	  m = -1;

	if (m > 0)
	  ret = swap(front, rear);
	else
	  ret = 1;

	if (ret == 0) {
#ifdef _DEBUG_
	  fprintf(stderr, "swaping %s and %s\n", pre, next);
#endif
	  if (dlp->tail == rear)
		dlp->tail = front;
	  if (dlp->head == front)
		dlp->head = rear;
	  front = dlp->cur;
	  rear = front->next;
	} else {
	  front = dlp->cur->pre;
	  rear = dlp->cur;
	}

	dlp->cur = front;
  }
}

int
dl_delete(const char *str, DLIST *dlp)
{
  assert((str != NULL) &&
		 (dlp != NULL) &&
		 !dl_empty(dlp));
  
  dlp->cur = dlp->head;
  while (dlp->cur) {
	if (0 == strncmp(str, dlp->cur->ent, strlen(str) + 1)) {
	  dlp->cur->deleted = 1;
	  dlp->len--;
	  return (0);
	}
	dlp->cur = dlp->cur->next;
  }
  return (0);
}

void
dl_foreach(DLIST *dlp, void (*func_p) (dl_node *np))
{
  assert((dlp != NULL) &&
		 (func_p != NULL) &&
		 !dl_empty(dlp));
  
  dlp->cur = dlp->head;
  while (dlp->cur) {
	func_p(dlp->cur);
	dlp->cur = dlp->cur->next;
  }
}

void
dl_clear(DLIST *dlp)
{
  dl_node *np;

  assert((dlp != NULL) &&
		 dl_empty(dlp));

  np = dlp->head;
  dlp->cur = dlp->head->next;

  while (np != NULL) {
	free(np);
	np = NULL;
	np = dlp->cur;
	if (dlp->cur != NULL) {
	  dlp->cur = dlp->cur->next;
	  dlp->len--;
	}
  }

  dlp->cur = dlp->head = dlp->tail = NULL;
  dlp->len = 0;
}

void
dl_free(DLIST *dlp)
{
  dl_node *np;

  if (dl_empty(dlp)) {
	free(dlp);
	dlp = NULL;
	return;
  }

  np = dlp->head;
  dlp->cur = dlp->head->next;
  
  while (np != NULL) {
	free(np);
	np = NULL;
	np = dlp->cur;
	if (dlp->cur != NULL)
	  dlp->cur = dlp->cur->next;
  }
  
  if (dlp != NULL) {
	free(dlp);
	dlp = NULL;
  }
}
