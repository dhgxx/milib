#include "stack.h"

STACK *
st_init(void)
{
  STACK *s;
  
  if ((s = malloc(sizeof(STACK)))) {
	s->size = 0;
	return (s);
  }

  return (NULL);
}

int
st_empty(STACK *s)
{
  if (s)
	return (s->top == NULL) ? 1 : 0;
  
  return (0);
}

st_node *
st_mknode(const char *item)
{
  st_node  *np;

  if (item && (np = malloc(sizeof(st_node)))) {

	bzero(np->entry, ST_ENT_SIZE);
	strlcpy(np->entry, item, strlen(item) + 1);
	np->next = NULL;

	return (np);
  }

  return (NULL);
}

int
st_push(const char *item, STACK *s)
{
  st_node  *np;
  
  if (s && item) {
  
	np = st_mknode(item);
	np->next = s->top;
	s->top = np;
	s->size++;
	return (1);
  }

  return (0);
}

char *
st_pop(STACK *s)
{
  char *item;
  st_node *np;
  
  if (!st_empty(s)
	  && (item = malloc(sizeof(ST_ENT_SIZE)))) {
  
	np = s->top;
	s->top = np->next;
	bzero(item, ST_ENT_SIZE);
	strlcpy(item, np->entry, strlen(np->entry) + 1);
	np->next = NULL;
	s->size--;
	free(np);

	return (item);
  }

  return (NULL);
}

void
st_free(STACK *s)
{
  char *item;

  while (!st_empty(s)) {
	
	item = st_pop(s);
	
	if (item) {
	  free(item);
	  item = NULL;
	}
  }
}

void
st_proc(STACK *s, void (*func_p) (const char *item))  
{
  st_node *np;
  
  if (!st_empty(s)) {
  
	np = s->top;
  
	while (np != NULL) {
	  func_p(np->entry);
	  np = np->next;
	}
  }
}
