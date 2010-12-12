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

#include "stack.h"

STACK *
st_init(void)
{
  STACK *st;
  
  if ((st = (STACK *)malloc(sizeof(STACK))) == NULL)
	return (NULL);

  st->top = NULL;
  st->size = 0;
  return (st);
}

int
st_empty(STACK **st)
{
  STACK *stp = *st;
  
  if (stp == NULL)
	return (1);
  
  if (stp->top == NULL &&
	  stp->size == 0)
	return (1);
  
  return (0);
}

st_node *
st_mknode(const char *str)
{
  st_node  *np;

  if (str == NULL)
	return (NULL);

  if ((np = (st_node *)malloc(sizeof(st_node))) == NULL)
	return (NULL);

  bzero(np->ent, ST_ENTSIZ);
  strlcpy(np->ent, str, ST_ENTSIZ);
  np->next = NULL;
  return (np);
}

int
st_push(const char *str, STACK **st)
{
  st_node  *np;
  STACK *stp = *st;
  
  if (str == NULL)
	return (-1);
  if (stp == NULL)
	return (-1);
    
  np = st_mknode(str);

  if (np != NULL) {
	np->next = stp->top;
	stp->top = np;
	stp->size++;
	return (0);
  }

  return (-1);
}

st_node *
st_pop(STACK **st)
{
  st_node *np;
  STACK *stp = *st;

  if (stp == NULL)
	return (NULL);
  if (st_empty(&stp))
	return (NULL);

  np = stp->top;
  stp->top = np->next;
  np->next = NULL;
  stp->size--;
  return (np);
}

void
st_free(STACK **st)
{
  st_node *np;
  STACK *stp;

  stp = *st;
  if (stp == NULL)
	return;

  if (st_empty(&stp)) {
	free(stp);
	stp = NULL;
	return;
  }

  do {
	np = st_pop(&stp);
	if (np != NULL) {
	  free(np);
	  np = NULL;
	}
  } while (st_empty(&stp) != 1);

  if (stp != NULL) {
	free(stp);
	stp = NULL;
  }
}

void
st_foreach(STACK **st, void (*func_p) (st_node **np))  
{
  st_node *np;
  STACK *stp = *st;
  
  if (stp == NULL)
	return;
  if (func_p == NULL)
	return;
  if (st_empty(&stp))
	return;
  
  np = stp->top;
 
  while (np != NULL) {
	func_p(&np);
	np = np->next;
  }
}
