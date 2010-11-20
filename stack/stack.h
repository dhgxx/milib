#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*A string stack implementation*/
#define ST_ENT_SIZE 256

typedef struct _st_node {
  char entry[ST_ENT_SIZE];
  struct _st_node *next;
} st_node;

typedef struct _stack {
  st_node *top;
  unsigned int size;
} STACK;


STACK *st_init(void);
int st_empty(STACK *);
st_node *st_pop(STACK *);
int st_push(const char *, STACK *);
st_node *st_mknode(const char *);
void st_proc(STACK *, void (*) (const st_node *));
void st_free(STACK **);

#endif /* _STACK_H_ */
