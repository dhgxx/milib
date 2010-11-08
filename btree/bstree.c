#include "bstree.h"

bst_node *
bst_mknode(const char *s)
{
  bst_node *np;
  
  if (s && (np = malloc(sizeof(bst_node)))) {

	bzero(np->node, BSTNODE_ENT_SIZE);
	strlcpy(np->node, s, strlen(s) + 1);
	np->left = NULL;
	np->right = NULL;
	return (np);
  } else {
	return (NULL);
  }
}

BSTREE *
bst_init(void)
{
  BSTREE *tp;

  tp = malloc(sizeof(BSTREE));
			  
  if (tp)
	tp->root = NULL;
  
  return (tp);
}
  
int
bst_empty(BSTREE *tp)
{
  return (tp->root == NULL ? 1 : 0);
}

bst_node *
bst_find(const char *s, bst_node *n)
{
  int m;
  bst_node *np;

  np = n;
  
  if (np) {

	m = strncmp(s, np->node, strlen(s) + 1);
	
	if (0 == m)
	  return (np);
	
	if (0 > m)
	  if (np->left)
		np = bst_find(s, np->left);

	if (0 < m)
	  if (np->right)
		np = bst_find(s, np->right);
  }
	
  return (np);
}

void
bst_insert(const char *s, BSTREE *tp)
{
  int m;
  bst_node *np, *new;

  np = bst_find(s, tp->root);
  new = bst_mknode(s);

  if (np) {

	m = strncmp(s, np->node, strlen(s) + 1);
	
	if (0 == m || 0 > m)	  
	  np->left = new;
	else	  
	  np->right = new;
	  
  } else {
	tp->root = new;
  }
}

void
bst_free(bst_node *np)
{
  if (np) {

	if (np->left)
	  bst_free(np->left);
	if (np->right)
	  bst_free(np->right);

	free(np);
	np = NULL;
	return;
  }
}

void
bst_preorder_proc(bst_node *n, void (*func_p) (const char *s))
{
    bst_node *np;

	if (n && func_p) {
	  
	  np = n;
	  
	  if (np) {
		
		func_p(np->node);

		if (np->left)
		  bst_preorder_proc(np->left, func_p);
		
		if (np->right)
		  bst_preorder_proc(np->right, func_p);
	  }
	}
}

void
bst_inorder_proc(bst_node *n, void (*func_p) (const char *s))
{
    bst_node *np;

	if (n && func_p) {
	  
	  np = n;
	  
	  if (np) {
		
		if (np->left)
		  bst_inorder_proc(np->left, func_p);
		
		func_p(np->node);
		
		if (np->right)
		  bst_inorder_proc(np->right, func_p);
	  }
	}
}

void
bst_postorder_proc(bst_node *n, void (*func_p) (const char *s))
{
    bst_node *np;

	if (n && func_p) {
	  
	  np = n;
	  
	  if (np) {
		
		if (np->left)
		  bst_postorder_proc(np->left, func_p);
		
		if (np->right)
		  bst_postorder_proc(np->right, func_p);
		
		func_p(np->node);
	  }
	}
}
