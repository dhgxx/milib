#include "bstree.h"

static bst_node *_bst_loc(const char *, bst_node *);
static void _bst_ins(const char *, bst_node *, int);
static void _bst_proc(bst_node *, BST_TRV_ORDER, void (*) (const char *));
static void _bst_free(bst_node *);

bst_node *
bst_mknode(const char *str)
{
  bst_node *np;
  
  if (str && (np = malloc(sizeof(bst_node)))) {

	bzero(np->node, BST_ENT_SIZE);
	strlcpy(np->node, str, strlen(str) + 1);
	np->left = NULL;
	np->right = NULL;
	np->deleted = 0;
	return (np);
  } else {
	return (NULL);
  }
}

BSTREE *
bst_init(void)
{
  BSTREE *tp;
			  
  if ((tp = malloc(sizeof(BSTREE))))
	tp->root = NULL;

  return (tp);
}
  
int
bst_empty(BSTREE *tp)
{
  if (tp)
	return ((tp->root == NULL) ? 1 : 0);

  return (0);
}

bst_node *
bst_find(const char *str, BSTREE *tp)
{
  return (_bst_loc(str, tp->root));
}

static bst_node *
_bst_loc(const char *str, bst_node *n)
{
  int m;
  bst_node *cur, *np;
  
  cur = np = n;
  
  if (np) {

	if (!np->deleted) {
	  
	  m = strncmp(str, np->node, strlen(str) + 1);
	
	  if (0 == m)
		return (np);
	
	  if (0 > m) {
		if (np->left)
		  cur = np = _bst_loc(str, np->left);
		else
		  return (np);
	  }
	  
	  if (0 < m) {
		if (np->right)
		  cur = np = _bst_loc(str, np->right);
		else
		  return (np);
	  }

	  return (np);
	}
  }
  
  return (cur);
}

void
bst_ins(const char *str, BSTREE *tp, int ic)
{  
  if (tp->root) {
	_bst_ins(str, tp->root, ic);
  } else {
	tp->root = bst_mknode(str);
  }
}

static void
_bst_ins(const char *str, bst_node *pos, int ic)
{
  int m;
  bst_node *np;

  np = _bst_loc(str, pos);
  
  if (np) {

	m = strncmp(str, np->node, strlen(str) + 1);

	if (ic == 1) {
	  if (0 > m || 0 == m) {
		if (!np->left)
		  np->left = bst_mknode(str);
		else
		  _bst_ins(str, np->left, ic);
	  }
	} else if (ic == 0) {
	  if (0 > m) {
		if (!np->left)
		  np->left = bst_mknode(str);
		else
		  _bst_ins(str, np->left, ic);
	  }
	}
	
	if (0 < m) {
	  if (!np->right)
		np->right = bst_mknode(str);
	  else
		_bst_ins(str, np->right, ic);
	}
  }
}

int
bst_del(const char *str, BSTREE *tp)
{
  bst_node *np;

  np = _bst_loc(str, tp->root);

  if (np != tp->root) {
	np->deleted = 1;
	return (1);
  }

  return (0);
}

void
bst_free(BSTREE *tp)
{
  if (tp)
	_bst_free(tp->root);
}

static void
_bst_free(bst_node *np)
{
  if (np) {

	if (np->left)
	  _bst_free(np->left);
	if (np->right)
	  _bst_free(np->right);

	free(np);
	np = NULL;
	return;
  }
}

void
bst_proc(BSTREE *tp, BST_TRV_ORDER odr, void (*func_p) (const char *str))
{
  _bst_proc(tp->root, odr, func_p);
}

static void
_bst_proc(bst_node *beg, BST_TRV_ORDER odr, void (*func_p) (const char *str))
{
    bst_node *np;

	if (beg && func_p) {
	  
	  np = beg;
	  
	  if (np) {
		switch (odr) {
		case BST_PREORDER:
		  if (!np->deleted)
			func_p(np->node);
		  if (np->left)
			_bst_proc(np->left, BST_PREORDER, func_p);
		  if (np->right)
			_bst_proc(np->right, BST_PREORDER, func_p);
		  break;
		case BST_INORDER:
		  if (np->left)
			_bst_proc(np->left, BST_INORDER, func_p);
		  if (!np->deleted)
			func_p(np->node);
		  if (np->right)
			_bst_proc(np->right, BST_INORDER, func_p);
		  break;
		default:
		case BST_POSTORDER:
		  if (np->left)
			_bst_proc(np->left, BST_POSTORDER, func_p);
		  if (np->right)
			_bst_proc(np->right, BST_POSTORDER, func_p);
		  if (!np->deleted)
			func_p(np->node);
		  break;
		}
	  }
	}
}
