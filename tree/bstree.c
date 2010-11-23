#include "bstree.h"

static bst_node *locate(const char *, bst_node *);
static int insert(const char *, bst_node **, int);
static void foreach(bst_node *, BST_TRV_ORDER, void (*) (const bst_node *));
static void mem_free(bst_node **);

bst_node *
bst_mknode(const char *str)
{
  bst_node *np;
  
  if (str == NULL)
	return (NULL);
  if (NULL == (np = (bst_node *)malloc(sizeof(bst_node))))
	return (NULL);

  bzero(np->node, BST_ENT_SIZE);
  strncpy(np->node, str, BST_ENT_SIZE);
  np->left = NULL;
  np->right = NULL;
  np->deleted = 0;
  return (np);
}

BSTREE *
bst_init(void)
{
  BSTREE *tp;
			  
  if (NULL == (tp = (BSTREE *)malloc(sizeof(BSTREE))))
	return (NULL);
  
  tp->root = NULL;
  tp->size = 0;
  return (tp);
}
  
int
bst_empty(BSTREE *tp)
{
  if (tp == NULL)
	return (1);
  
  if (tp->root == NULL &&
	  tp->size == 0)
	return (1);

  return (0);
}

bst_node *
bst_find(const char *str, BSTREE *tp)
{
  if (str == NULL)
	return (NULL);
  if (tp == NULL)
	return (NULL);
  if (bst_empty(tp))
	return (NULL);
  
  return (locate(str, tp->root));
}

static bst_node *
locate(const char *str, bst_node *n)
{
  int m;
  bst_node *cur, *np;
  
  if (str == NULL)
	return (NULL);
  if (n == NULL)
	return (NULL);
  
  cur = np = n;
  
  if (np->deleted != 1) {
	m = strncmp(str, np->node, strlen(str) + 1);
	
	if (0 == m)
	  return (np);
	
	if (0 > m) {
	  if (np->left != NULL)
		cur = np = locate(str, np->left);
	  else
		return (np);
	}
	  
	if (0 < m) {
	  if (np->right != NULL)
		cur = np = locate(str, np->right);
	  else
		return (np);
	}
	
	return (np);
  }
  
  return (cur);
}

int
bst_ins(const char *str, BSTREE **t, const int ic)
{
  BSTREE *tp = *t;
  
  if (str == NULL)
	return (-1);
  if (tp == NULL)
	return (-1);

  if (bst_empty(tp)) {

	if ((tp->root = bst_mknode(str)) == NULL)
	  return (-1);
	
	tp->size++;
	return (0);
  }
  
  if (0 == insert(str, &(tp->root), ic)) {
	tp->size++;
	return (0);
  }

  return (-1);
}

static int
insert(const char *str, bst_node **src, const int ic)
{
  int m, ret;
  bst_node *np;
  bst_node *pos = *src;

  if (str == NULL)
	return (-1);
  if (pos == NULL)
	return (-1);

  ret = -1;
  np = locate(str, pos);
  m = strncmp(str, np->node, strlen(str) + 1);

  if (ic == 1 && m == 0) {
	if (np->left == NULL) {
	  if (NULL != (np->left = bst_mknode(str)))
		ret = 0;
	} else {
	  ret = insert(str, &(np->left), ic);
	}
  }

  if (0 > m) {	  
	if (np->left == NULL) {
	  if (NULL != (np->left = bst_mknode(str)))
		ret = 0;
	} else {
	  ret = insert(str, &(np->left), ic);
	}
  }
	
  if (0 < m) {	  
	if (np->right == NULL) {
	  if (NULL != (np->right = bst_mknode(str)))
		ret = 0;
	} else {
	  ret = insert(str, &(np->right), ic);
	}
  }

  return (ret);
}

int
bst_del(const char *str, BSTREE **t)
{
  bst_node *np;
  BSTREE *tp = *t;

  if (str == NULL)
	return (-1);
  if (tp == NULL)
	return (-1);
  
  np = locate(str, tp->root);

  if (np != NULL) {
	np->deleted = 1;
	tp->size--;
	return (0);
  }

  return (-1);
}

void
bst_free(BSTREE **tp)
{
  BSTREE *p;

  p = *tp;
  if (p == NULL)
	return;
  
  mem_free(&(p->root));
  if (p != NULL) {
	free(p);
	p = NULL;
  }
}

static void
mem_free(bst_node **np)
{
  bst_node *p;

  p = *np;
  if (p == NULL)
	return;
  
  if (p->left != NULL)
	mem_free(&(p->left));
  if (p->right != NULL)
	mem_free(&(p->right));

  free(p);
  p = NULL;
}

void
bst_foreach(BSTREE *tp, BST_TRV_ORDER odr, void (*func_p) (const bst_node *node))
{  
  if (tp == NULL)
	return;
  if (func_p == NULL)
	return;
  
  foreach(tp->root, odr, func_p);
}

static void
foreach(bst_node *beg, BST_TRV_ORDER odr, void (*func_p) (const bst_node *node))
{
    bst_node *np;

	if (beg == NULL)
	  return;
	if (func_p == NULL)
	  return;
		  
	np = beg;
	
	switch (odr) {
	case BST_PREORDER:
	  if (np->deleted != 1)
		func_p(np);
	  if (np->left != NULL)
		foreach(np->left, BST_PREORDER, func_p);
	  if (np->right != NULL)
		foreach(np->right, BST_PREORDER, func_p);
	  break;
	case BST_INORDER:
	  if (np->left != NULL)
		foreach(np->left, BST_INORDER, func_p);
	  if (np->deleted != 1)
		func_p(np);
	  if (np->right != NULL)
		foreach(np->right, BST_INORDER, func_p);
	  break;
	default:
	case BST_POSTORDER:
	  if (np->left != NULL)
		foreach(np->left, BST_POSTORDER, func_p);
	  if (np->right != NULL)
		foreach(np->right, BST_POSTORDER, func_p);
	  if (np->deleted != 1)
		func_p(np);
	  break;
	}
}
