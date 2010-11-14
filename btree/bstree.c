#include "bstree.h"

static bst_node *_bst_loc(const char *, bst_node *);
static void _bst_ins(const char *, bst_node *, int);
static void _bst_proc(bst_node *, BST_TRV_ORDER, void (*) (const bst_node *));
static void _bst_free(bst_node *);

bst_node *
bst_mknode(const char *str)
{
  bst_node *np;
  
  if (str == NULL)
	return (NULL);
  if ((np = malloc(sizeof(bst_node))) == NULL)
	return (NULL);

  bzero(np->node, BST_ENT_SIZE);
  strlcpy(np->node, str, strlen(str) + 1);
  np->left = NULL;
  np->right = NULL;
  np->deleted = 0;
  return (np);
}

BSTREE *
bst_init(void)
{
  BSTREE *tp;
			  
  if ((tp = malloc(sizeof(BSTREE))) == NULL)
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
  
  return (_bst_loc(str, tp->root));
}

static bst_node *
_bst_loc(const char *str, bst_node *n)
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
		cur = np = _bst_loc(str, np->left);
	  else
		return (np);
	}
	  
	if (0 < m) {
	  if (np->right != NULL)
		cur = np = _bst_loc(str, np->right);
	  else
		return (np);
	}
	
	return (np);
  }
  
  return (cur);
}

int
bst_ins(const char *str, BSTREE *tp, const int ic)
{
  if (str == NULL)
	return (0);
  if (tp == NULL)
	return (0);

  if (bst_empty(tp)) {

	if ((tp->root = bst_mknode(str)) == NULL)
	  return (0);
	
	tp->size++;
	return (1);
  }
  
  _bst_ins(str, tp->root, ic);
  tp->size++;
  return (1);
}

static void
_bst_ins(const char *str, bst_node *pos, const int ic)
{
  int m;
  bst_node *np;

  if (str == NULL)
	return;
  if (pos == NULL)
	return;
  
  np = _bst_loc(str, pos);
  m = strncmp(str, np->node, strlen(str) + 1);

  if (ic == 1 && m == 0) {	  
	if (np->left != NULL)		
	  np->left = bst_mknode(str);
	else
	  _bst_ins(str, np->left, ic);
  }

  if (0 > m) {	  
	if (np->left != NULL)
	  np->left = bst_mknode(str);
	else
	  _bst_ins(str, np->left, ic);
  }
	
  if (0 < m) {	  
	if (np->right != NULL)
	  np->right = bst_mknode(str);
	else
	  _bst_ins(str, np->right, ic);
  }
}

int
bst_del(const char *str, BSTREE *tp)
{
  bst_node *np;

  if (str == NULL)
	return (0);
  if (tp == NULL)
	return (0);
  
  np = _bst_loc(str, tp->root);

  if (np != NULL) {
	np->deleted = 1;
	tp->size--;
	return (1);
  }

  return (0);
}

void
bst_free(BSTREE *tp)
{
  if (tp == NULL)
	return;
  
  _bst_free(tp->root);
  free(tp);
  tp = NULL;
}

static void
_bst_free(bst_node *np)
{
  if (np == NULL)
	return;
  
  if (np->left != NULL)
	_bst_free(np->left);
  if (np->right != NULL)
	_bst_free(np->right);

  free(np);
  np = NULL;
}

void
bst_proc(BSTREE *tp, BST_TRV_ORDER odr, void (*func_p) (const bst_node *np))
{
  if (tp == NULL)
	return;
  if (func_p == NULL)
	return;
  
  _bst_proc(tp->root, odr, func_p);
}

static void
_bst_proc(bst_node *beg, BST_TRV_ORDER odr, void (*func_p) (const bst_node *np))
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
		_bst_proc(np->left, BST_PREORDER, func_p);
	  if (np->right != NULL)
		_bst_proc(np->right, BST_PREORDER, func_p);
	  break;
	case BST_INORDER:
	  if (np->left != NULL)
		_bst_proc(np->left, BST_INORDER, func_p);
	  if (np->deleted != 1)
		func_p(np);
	  if (np->right != NULL)
		_bst_proc(np->right, BST_INORDER, func_p);
	  break;
	default:
	case BST_POSTORDER:
	  if (np->left != NULL)
		_bst_proc(np->left, BST_POSTORDER, func_p);
	  if (np->right != NULL)
		_bst_proc(np->right, BST_POSTORDER, func_p);
	  if (np->deleted != 1)
		func_p(np);
	  break;
	}
}
