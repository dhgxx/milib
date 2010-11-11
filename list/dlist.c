#include "dlist.h"

/* static void _dl_ins_after(dl_node *, dl_node *); */
static void _dl_ins_before(dl_node *, dl_node *);

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
  if (dl) {
	
	if (dl->head == NULL &&
		dl->tail == NULL &&
		dl->cur == NULL &&
		dl->len == 0)
	  return (1);
  }

  return (0);
}

int
dl_append(const char *s, DLIST *dl)
{
  dl_node *new;
  
  if (dl) {
	
	new = dl_mknode(s);

	if (dl_empty(dl)) {
	  dl->head = new;
	} else {
	  dl->tail->next = new;
	  new->pre = dl->tail;
	}
	
	dl->cur = new;
	dl->tail = new;
	dl->len++;
	return (1);
  }

  return (0);
}

/*
static void
_dl_ins_after(dl_node *np, dl_node *new)
{
  new->pre = np;
  new->next = np->next;
  np->next->pre = new;
  np->next = new;
}
*/

static void
_dl_ins_before(dl_node *np, dl_node *new)
{
  new->next = np;
  new->pre = np->pre;
  np->pre->next = new;
  np->pre = new;
}

int
dl_ins_at_pos(const char *s, int pos, DLIST *dl)
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

	  new->next = dl->head;
	  dl->head->pre = new;
	  dl->head = new;
	  dl->len++;
	  return (1);
	}

	if (pos > 0 && pos < dl->len) {

	  np = dl->head;

	  for (i = 0; i < pos; i++)
		np = np->next;

	  _dl_ins_before(np, new);
	  dl->len++;
	  return (1);  
	}

	if (pos >= dl->len) {
	  
	  new->pre = dl->tail->pre;
	  dl->tail->next = new;
	  dl->tail = new;
	  dl->len++;
	  return (1);
	}
  }

  return (0);
}

int
dl_ins_at_val(const char *s, const char *t, DLIST *dl)
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
	while (np) {

	  if (0 == strncmp(t, np->node, strlen(t) + 1)) {
	
		if (np == dl->head) {
		  new->next = dl->head;
		  dl->head->pre = new;
		  dl->head = new;
		  dl->len++;
		  return (1);
		}

		_dl_ins_before(np, new);
		dl->len++;
		return (1);
	  }
	  	 
	  np = np->next;
	}

	new->pre = dl->tail->pre;
	dl->tail->next = new;
	dl->tail = new;
	dl->len++;
	return (1);
  }
  
  return (0);
}

int
dl_delete(const char *s, DLIST *dl)
{
  dl_node *np;
  
  if (s && !dl_empty(dl)) {
	
	np = dl->head;
	while (np) {
	  if (0 == strncmp(s, np->node, strlen(s) + 1)) {
		np->deleted = 1;
		dl->len--;
		return (1);
	  }
	  np = np->next;
	}
  }

  return (0);
}

void
dl_proc(DLIST *dl, void (*func_p) (const char *s))
{
  dl_node *np;
  
  if (dl && func_p) {
	if (!dl_empty(dl)) {
	  np = dl->head;
	  while (np) {
		if (!np->deleted)
		  func_p(np->node);
		dl->cur = np;
		np = np->next;
	  }
	}
  }
}

void
dl_free(DLIST *dl)
{
  dl_node *np;
  
  if (!dl) {
	dl->cur = np = dl->tail;
	while (dl->cur) {
	  dl->cur = dl->cur->pre;
	  free(np);
	  np = NULL;
	}
  }
}
