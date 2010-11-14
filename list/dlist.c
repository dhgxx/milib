#include "dlist.h"

static void _dl_ins_after(dl_node *, dl_node *);
static void _dl_ins_before(dl_node *, dl_node *);

dl_node *
dl_mknode(const char *str)
{
  dl_node *np;
  
  if (str == NULL)
	return (NULL);
  
  if ((np = malloc(sizeof(dl_node))) == NULL)
	return (NULL);
  
  bzero(np->node, DL_ENT_SIZE);
  strncpy(np->node, str, strlen(str) + 1);
  np->deleted = 0;
  np->pre = NULL;
  np->next = NULL;
  return (np);
}

DLIST *
dl_init(void)
{
  DLIST *dl;
  
  if ((dl = malloc(sizeof(DLIST))) == NULL)
	return (NULL);
  
  dl->head = NULL;
  dl->tail = NULL;
  dl->cur = NULL;
  dl->len = 0;
  return (dl);
}

int
dl_empty(const DLIST *dl)
{
  if (dl == NULL)
	return (1);

  if ((dl->head == NULL) &&
	  (dl->tail == NULL) &&
	  (dl->cur == NULL) &&
	  (dl->len == 0)) {
	return (1);
  }

  return (0);
}

int
dl_append(const char *str, DLIST *dl)
{
  dl_node *new;
  
  if (dl == NULL)
	return (0);

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

static void
_dl_ins_after(dl_node *np, dl_node *new)
{
  new->pre = np;
  if (np->next != NULL) {
	new->next = np->next;
	np->next->pre = new;
  }
  np->next = new;
}

static void
_dl_ins_before(dl_node *np, dl_node *new)
{
  new->next = np;
  if (np->pre != NULL) {	
	new->pre = np->pre;
	np->pre->next = new;
  }
  np->pre = new;
}

int
dl_ins_at_pos(const char *str, int pos, DLIST *dl, const int before)
{
  int i;
  dl_node *new, *np;
  
  if (str == NULL)
	return (0);

  if (dl == NULL)
	return (0);
	
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

	  if (before == 1)
		_dl_ins_before(np, new);
	  else
		_dl_ins_after(np, new);
	  
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

int
dl_ins_at_val(const char *str, const char *pos, DLIST *dl, const int before)
{
  dl_node *new, *np;
  
  if ((str == NULL) ||
	  (pos == NULL))
	return (0);

  if (dl == NULL)
	return (0);

  dl->cur = new = dl_mknode(str);
	
  if (dl_empty(dl)) {
	dl->head = dl->tail = new;
	dl->len++;
  } else {
	np = dl->head;
	while (np) {
	  if (0 == strncmp(pos, np->node, strlen(pos) + 1)) {
		if (before == 1)
		  _dl_ins_before(np, new);
		else
		  _dl_ins_after(np, new);
		
		if (np == dl->head)
		  dl->head = new;
		if (np == dl->tail)
		  dl->tail = new;
		
		dl->len++;
		break;
	  }
	  np = np->next;
	}
  }
  return (1);
}

int
dl_delete(const char *str, DLIST *dl)
{  
  if (str == NULL)
	return (0);

  if (dl == NULL)
	return (0);
  
  if (!dl_empty(dl)) {
	dl->cur = dl->head;
	while (dl->cur) {
	  if (0 == strncmp(str, dl->cur->node, strlen(str) + 1)) {
		dl->cur->deleted = 1;
		dl->len--;
		return (1);
	  }
	  dl->cur = dl->cur->next;
	}
	return (1);
  }
  return (0);
}

void
dl_proc(DLIST *dl, void (*func_p) (const dl_node *np))
{
  if (dl == NULL)
	return;

  if (func_p == NULL)
	return;

  if (!dl_empty(dl)) {
	dl->cur = dl->head;
	while (dl->cur) {
	  if (dl->cur->deleted != 1)
		func_p(dl->cur);
	  dl->cur = dl->cur->next;
	}
  }
}

void
dl_free(DLIST *dl)
{
  dl_node *np;
  
  if (dl == NULL)
	return;

  np = dl->tail;
  dl->cur = dl->tail->pre;
  
  while (np) {
	free(np);
	np = NULL;
	np = dl->cur;
	dl->cur = dl->cur->pre;
  }
}
