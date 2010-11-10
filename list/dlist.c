#include "dlist.h"

dl_node *
dl_mknode(const char *s)
{
  dl_node *n;
  
  if (s && (n = malloc(sizeof(dl_node)))) {
	bzero(n->node, DL_ENT_SIZE);
	strncpy(n->node, s, strlen(s) + 1);
	n->deleted = 0;
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
	} else {
	  dl->tail->next = n;
	  n->pre = dl->tail;
	}
	
	dl->cur = n;
	dl->tail = n;
	dl->len++;
	return (1);
  }

  return (0);
}

int
dl_ins_at_pos(const char *s, int pos,  DLIST *dl)
{
  int i;
  dl_node *new, *np;
  
  if (s && dl) {
	
	new = dl_mknode(s);
	dl->cur = new;
	
	if (dl_empty(dl)) {

	  dl->head = dl->tail = new;
	  dl->len++;
	  return (1);
	}

	if (pos <= 0) {

	  np = dl->head;
	  new->next = np;
	  np->pre = new;
	  
	  dl->head = new;
	  dl->cur = new;
	  dl->len++;
	  return (1);
	}

	if (pos > 0 && pos <= dl->len) {

	  np = dl->head;

	  for (i = 1; i < pos; i++)
		np = np->next;

	  new->next = np;
	  new->pre = np->pre;
	  np->pre = new;
	  dl->len++;
	  return (1);  
	}

	if (pos > dl->len) {

	  np = dl->tail;
	  np->next = new;
	  new->pre = np;
	  dl->len++;
	  return (1);
	}
  }

  return (0);
}

int
dl_ins_at_val(const char *s, const char *t, DLIST *dl, int before)
{
  dl_node *new, *np;
  
  if (s && t && dl) {

	new = dl_mknode(s);
	dl->cur = new;
	
	if (dl_empty(dl)) {
	  dl->head = dl->tail = new;
	  dl->len++;
	  return (1);
	}
	
	np = dl->head;
	while (np && (0 != strncmp(t, np->node, strlen(t) + 1)))
	  np = np->next;

	if (before == 1)
	  np = np->pre;
	
	if (np == dl->head) {
	  dl_ins_at_pos(s, 0, dl);
	  return (1);
	}

	if (np == dl->tail) {
	  dl_ins_at_pos(s, dl->len, dl);
	  return (1);
	}

	new->pre = np;
	new->next = np->next;
	np->next = new;
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
