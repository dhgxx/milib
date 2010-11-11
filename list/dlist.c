#include "dlist.h"

/* static void _dl_ins_after(dl_node *, dl_node *); */
static void _dl_ins_before(dl_node *, dl_node *);

dl_node *
dl_mknode(const char *str)
{
  dl_node *np;
  
  if (str && (np = malloc(sizeof(dl_node)))) {
	bzero(np->node, DL_ENT_SIZE);
	strncpy(np->node, str, strlen(str) + 1);
	np->deleted = 0;
	np->pre = NULL;
	np->next = NULL;
  }

  return (np);
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
dl_append(const char *str, DLIST *dl)
{
  dl_node *new;
  
  if (dl) {
	
	new = dl_mknode(str);

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
dl_ins_at_pos(const char *str, int pos, DLIST *dl)
{
  int i;
  dl_node *new, *np;
  
  if (str && dl) {
	
	new = dl_mknode(str);
	
	if (dl_empty(dl)) {

	  dl->cur = dl->head = dl->tail = new;
	  dl->len++;
	} else {

	  dl->cur = new;
	  
	  if (pos <= 0) {

		new->next = dl->head;
		dl->head->pre = new;
		dl->head = new;
		dl->len++;
	  }

	  if (pos > 0 && pos < dl->len) {

		np = dl->head;

		for (i = 0; i < pos && np; i++)
		  np = np->next;

		_dl_ins_before(np, new);
		dl->len++;
	  }

	  if (pos >= dl->len) {
	  
		new->pre = dl->tail->pre;
		dl->tail->next = new;
		dl->tail = new;
		dl->len++;
	  }
	}

	return (1);
  }

  return (0);
}

int
dl_ins_at_val(const char *str, const char *pos, DLIST *dl)
{
  dl_node *new, *np;
  
  if (str && pos && dl) {

	new = dl_mknode(str);
	
	if (dl_empty(dl)) {
	  
	  dl->cur = dl->head = dl->tail = new;
	  dl->len++;
	} else {

	  dl->cur = new;
	  np = dl->head;
	  
	  while (np) {

		if (0 == strncmp(pos, np->node, strlen(pos) + 1)) {
	
		  _dl_ins_before(np, new);
		  dl->len++;
		}
	  	 
		np = np->next;
	  }
	}

	return (1);
  }
  
  return (0);
}

int
dl_delete(const char *str, DLIST *dl)
{  
  if (str && !dl_empty(dl)) {
	
	dl->cur = dl->head;
	while (dl->cur) {
	  if (0 == strncmp(str, dl->cur->node, strlen(str) + 1)) {
		dl->cur->deleted = 1;
		dl->len--;
		return (1);
	  }
	  dl->cur = dl->cur->next;
	}
  }

  return (0);
}

void
dl_proc(DLIST *dl, void (*func_p) (const char *str))
{
  if (dl && func_p) {
	if (!dl_empty(dl)) {
	  dl->cur = dl->head;
	  while (dl->cur) {
		if (!dl->cur->deleted)
		  func_p(dl->cur->node);
		dl->cur = dl->cur->next;
	  }
	}
  }
}

void
dl_free(DLIST *dl)
{
  dl_node *np;
  
  if (!dl) {
	
	np = dl->tail;
	dl->cur = dl->tail->pre;
	while (np) {
	  free(np);
	  np = NULL;
	  np = dl->cur;
	  dl->cur = dl->cur->pre;
	}
  }
}
