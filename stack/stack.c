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
st_empty(STACK *st)
{
  if (st == NULL)
	return (1);
  
  if (st->top == NULL &&
	  st->size == 0)
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

  bzero(np->entry, ST_ENT_SIZE);
  strncpy(np->entry, str, ST_ENT_SIZE);
  np->next = NULL;
  return (np);
}

int
st_push(const char *str, STACK *st)
{
  st_node  *np;
  
  if (str == NULL)
	return (-1);
  if (st == NULL)
	return (-1);
    
  np = st_mknode(str);

  if (np != NULL) {
	np->next = st->top;
	st->top = np;
	st->size++;
	return (0);
  }

  return (-1);
}

st_node *
st_pop(STACK *st)
{
  st_node *np;

  if (st == NULL)
	return (NULL);
  if (st_empty(st))
	return (NULL);

  np = st->top;
  st->top = np->next;
  np->next = NULL;
  st->size--;
  return (np);
}

void
st_free(STACK *st)
{
  st_node *np;

  if (st == NULL)
	return;

  if (st_empty(st)) {
	free(st);
	st = NULL;
	return;
  }

  do {
	np = st_pop(st);
	if (np != NULL) {
	  free(np);
	  np = NULL;
	}
  } while (st_empty(st) != 1);

  if (st != NULL) {
	free(st);
	st = NULL;
  }
}

void
st_proc(STACK *st, void (*func_p) (const st_node *np))  
{
  st_node *np;

  if (st == NULL)
	return;
  if (func_p == NULL)
	return;
  if (st_empty(st))
	return;
  
  np = st->top;
 
  while (np != NULL) {
	func_p(np);
	np = np->next;
  }
}
