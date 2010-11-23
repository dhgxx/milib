#include "tree.h"

static void foreach(tr_node *, void (*)(const tr_node *));
static tr_node *locate(const char *, tr_node *);
static void mem_free(tr_node **);

tr_node *
tr_mknode(const char *str)
{
  tr_node *np;
  
  if (str == NULL)
	return (NULL);

  np = (tr_node *)malloc(sizeof(tr_node));

  if (np != NULL) {
	bzero(np->ent, TR_ENT_SIZE);
	strncpy(np->ent, str, TR_ENT_SIZE);
	np->sbl = NULL;
	np->eld = NULL;
	np->prt = NULL;
	np->cld = NULL;
  }

  return (np);
}

TREE *
tr_init(void)
{
  TREE *tp;

  tp = (TREE *)malloc(sizeof(TREE));

  if (tp != NULL) {
	tp->root = NULL;
	tp->size = 0;
  }

  return (tp);
}

int
tr_empty(TREE *tp)
{
  if (tp == NULL)
	return (1);

  if (tp->root == NULL &&
	  tp->size == 0)
	return (1);

  return (0);
}

void
tr_free(TREE **tp)
{
  TREE *p;

  p = *tp;

  if (p == NULL)
	return;
  if (tr_empty(p)) {
	free(p);
	p = NULL;
	return;
  }

  if (p->root != NULL)
	mem_free(&(p->root));

  if (p != NULL) {
	free(p);
	p = NULL;
  }
}

tr_node *
tr_find(const char *str, TREE *tp)
{
  tr_node *np;
  
  if (str == NULL)
	return (NULL);
  if (tp == NULL)
	return (NULL);
  if (tr_empty(tp))
	return (NULL);

  return (np = locate(str, tp->root));
}

void
tr_foreach(TREE *tp, void (*func_p)(const tr_node *np))
{  
  if (tp == NULL)
	return;
  if (func_p == NULL)
	return;
  if (tr_empty(tp))
	return;

  foreach(tp->root, func_p);
}

static void
foreach(tr_node *np, void (*func_p)(const tr_node *np))
{
  if (np == NULL)
	return;
  if (func_p == NULL)
	return;

  func_p(np);

  if (np->sbl != NULL)
	foreach(np->sbl, func_p);
  if (np->cld != NULL)
	foreach(np->cld, func_p);
}

static tr_node *
locate(const char *str, tr_node *np)
{
  if (str == NULL)
	return (NULL);
  if (np == NULL)
	return (NULL);
  if (np->ent == NULL)
	return (NULL);
  
  if (0 == strncmp(str, np->ent, strlen(str) + 1))
	return (np);

  if (np->sbl != NULL)
	np = locate(str, np->sbl);
  if (np->cld != NULL)
	np = locate(str, np->cld);

  return (np);
}

int
tr_add_sbl(const char *str, const char *src, TREE *tp)
{
  tr_node *np;
  
  if (str == NULL)
	return (-1);
  if (src == NULL)
	return (-1);
  if (tp == NULL)
	return (-1);
  
  if (tr_empty(tp)) {
	tp->cur = tp->root = tr_mknode(str);
	tp->size++;
	return (0);
  }

  if (NULL == (np = locate(src, tp->root)))
	return (-1);

  while (np->sbl != NULL)
	np = np->sbl;

  tp->cur = np->sbl = tr_mknode(str);
  np->sbl->eld = np;
  tp->size++;
  return (0);
}

int
tr_add_cld(const char *str, const char *src, TREE *tp)
{
  tr_node *np;

  if (str == NULL)
	return (-1);
  if (src == NULL)
	return (-1);
  if (tp == NULL)
	return (-1);

  if (tr_empty(tp)) {
	tp->cur = tp->root = tr_mknode(str);
	tp->size++;
	return (0);
  }

  if (NULL == (np = locate(src, tp->root)))
	return (-1);

  if (np->cld == NULL) {  
	tp->cur = np->cld = tr_mknode(str);
	np->cld->prt = np;
	tp->size++;
	return (0);
  }

  np = np->cld;
  while (np->sbl != NULL)
	np = np->sbl;

  tp->cur = np->sbl = tr_mknode(str);
  np->sbl->eld = np;
  tp->size++;
  return (0);
}
  
static void
mem_free(tr_node **np)
{
  tr_node *p;

  p = *np;

  if (p == NULL)
	return;
  
  if (p->cld != NULL)
	mem_free(&(p->cld));
  if (p->sbl != NULL)
	mem_free(&(p->sbl));
  
  if (p->cld == NULL &&
	  p->sbl == NULL) {
	free(p);
	p = NULL;
	return;
  }
}
