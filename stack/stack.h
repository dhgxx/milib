#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*A string stack implementation*/
#define STACK_ENT_SIZE 256

typedef struct _st_node {
  char entry[STACK_ENT_SIZE];
  struct _st_node *next;
} st_node;

typedef struct _stack {
  st_node *top;
} STACK;

void st_error(const char *);

/* return NULL if failed, a pointer to a stack otherwise. */
STACK *st_init(void);

/* return 0 if stack empty, 1 otherwise */
int st_empty(STACK *);

/* return NULL if failed, a pointer to stack node if success. */
char *st_pop(STACK *);
int st_push(const char *, STACK *);
st_node *st_mknode(const char *);

void st_proc(STACK *, void (*) (const char *));
void st_clear(STACK *);

#endif /* _STACK_H_ */
