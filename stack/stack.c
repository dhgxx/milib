#include "stack.h"

STACK *
st_init(void)
{
  STACK *st;
  
  if ((st = malloc(sizeof(STACK))) == NULL)
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

  if ((np = malloc(sizeof(st_node))) == NULL)
	return (NULL);
  
  bzero(np->entry, ST_ENT_SIZE);
  strlcpy(np->entry, str, strlen(str) + 1);
  np->next = NULL;
  return (np);
}

int
st_push(const char *str, STACK *st)
{
  st_node  *np;
  
  if (str == NULL)
	return (0);
  if (st == NULL)
	return (0);
    
  np = st_mknode(str);
  np->next = st->top;
  st->top = np;
  st->size++;
  return (1);
}

char *
st_pop(STACK *st)
{
  char *str;
  st_node *np;

  if (st == NULL)
	return (NULL);
  if (st_empty(st))
	return (NULL);
  if ((str = malloc(sizeof(ST_ENT_SIZE))) == NULL)
	return (NULL);
  
  np = st->top;
  st->top = np->next;
  bzero(str, ST_ENT_SIZE);
  strlcpy(str, np->entry, strlen(np->entry) + 1);
  np->next = NULL;
  st->size--;
  free(np);
  return (str);
}

void
st_free(STACK *st)
{
  char *str;

  if (st == NULL)
	return;
  
  while (!st_empty(st)) {
	str = st_pop(st);
	
	if (str == NULL)
	  return;
	
	free(str);
	str = NULL;
  }
}

void
st_proc(STACK *st, void (*func_p) (const char *str))  
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
	func_p(np->entry);
	np = np->next;
  }
}
