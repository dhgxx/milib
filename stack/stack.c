#include "stack.h"

STACK *
st_init(void)
{
  STACK *st;
  
  if ((st = malloc(sizeof(STACK)))) {
	st->top = NULL;
	st->size = 0;
  }

  return (st);
}

int
st_empty(STACK *st)
{
  if (st) {
	if (st->top == NULL &&
		st->size == 0)
	  return (1);
  }
  
  return (0);
}

st_node *
st_mknode(const char *str)
{
  st_node  *np;

  if (str && (np = malloc(sizeof(st_node)))) {

	bzero(np->entry, ST_ENT_SIZE);
	strlcpy(np->entry, str, strlen(str) + 1);
	np->next = NULL;

	return (np);
  }

  return (NULL);
}

int
st_push(const char *str, STACK *st)
{
  st_node  *np;
  
  if (st && str) {
  
	np = st_mknode(str);
	np->next = st->top;
	st->top = np;
	st->size++;
	return (1);
  }

  return (0);
}

char *
st_pop(STACK *st)
{
  char *str;
  st_node *np;
  
  if (!st_empty(st)
	  && (str = malloc(sizeof(ST_ENT_SIZE)))) {
  
	np = st->top;
	st->top = np->next;
	bzero(str, ST_ENT_SIZE);
	strlcpy(str, np->entry, strlen(np->entry) + 1);
	np->next = NULL;
	st->size--;
	free(np);

	return (str);
  }

  return (NULL);
}

void
st_free(STACK *st)
{
  char *str;

  while (!st_empty(st)) {
	
	str = st_pop(st);
	
	if (str) {
	  free(str);
	  str = NULL;
	}
  }
}

void
st_proc(STACK *st, void (*func_p) (const char *str))  
{
  st_node *np;
  
  if (!st_empty(st)) {
  
	np = st->top;
  
	while (np != NULL) {
	  func_p(np->entry);
	  np = np->next;
	}
  }
}
