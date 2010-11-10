#include "dlist.h"

dl_node *
dl_mknode(const char *s)
{
  dl_node *n;
  
  if (s && (n = malloc(sizeof(dl_node)))) {
	bzero(n->node, DL_ENT_SIZE);
	strncpy(n->node, s, strlen(s) + 1);
	n->pre = NULL;
	n->next = NULL;
  }

  return (n);
}

DLIST *
dl_init(void)
{
  DLIST *dl;
  
  if ((dl = malloc(sizeof(DLIST)))) {
	dl->head = NULL;
	dl->tail = NULL;
	dl->cur = NULL;
	dl->len = 0;
  }

  return (dl);
}

int
dl_empty(DLIST *dl)
{
  if (!dl)
	return (1);
  if (dl->head == NULL &&
	  dl->len == 0)
	return (1);

  return (0);
}

int
dl_append(const char *s, DLIST *dl)
{
  dl_node *n;
  
  if (dl) {
	
	n = dl_mknode(s);

	if (dl_empty(dl)) {
	  dl->head = n;
	  n->pre = dl->head;
	} else {
	  dl->cur->next = n;
	  n->pre = dl->cur;
	}
	
	dl->cur = n;
	dl->tail = n;
	dl->len++;
	return (1);
  }

  return (0);
}

int
dl_delete(const char *s, DLIST *dl)
{
  dl_node *n;
  
  if (s && !dl_empty(dl)) {
	
	n = dl->head;
	while (n) {
	  if (0 == strncmp(s, n->node, strlen(s) + 1)) {
		n->deleted = 1;
		dl->len--;
		return (1);
	  }
	  n = n->next;
	}
  }

  return (0);
}

void
dl_proc(DLIST *dl, void (*func_p) (const char *s))
{
  dl_node *n;
  
  if (dl && func_p) {
	if (!dl_empty(dl)) {
	  n = dl->head;
	  while (n) {
		if (!n->deleted)
		  func_p(n->node);
		dl->cur = n;
		n = n->next;
	  }
	}
  }
}

void
dl_free(DLIST *dl)
{
  dl_node *n;
  
  if (!dl) {
	n = dl->tail;
	while (n) {
	  free(n);
	  n = NULL;
	  n = n->pre;
	}
  }
}
