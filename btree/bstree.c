#include "bstree.h"

bst_node *
bst_mknode(const char *s)
{
  bst_node *np;
  
  if (s == NULL)
	return (NULL);

  if ((np = malloc(sizeof(bst_node))) == NULL)
	return (NULL);

  bzero(np->node, BSTNODE_ENT_SIZE);
  strlcpy(np->node, s, strlen(s) + 1);
  np->left = NULL;
  np->right = NULL;

  return np;
}

BSTREE *
bst_init(void)
{
  BSTREE *tp;

  if ((tp = malloc(sizeof(BSTREE))) == NULL)
	return (NULL);

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
  bst_node *np;

  np = n;
  
  if (np != NULL) {

	if (0 == strncmp(s, np->node, strlen(s) + 1))
	  return (np);
	
	if (0 > strncmp(s, np->node, strlen(s) + 1)) {
	  
	  if (np->left != NULL)
		np = bst_find(s, np->left);
	}

	if (0 < strncmp(s, np->node, strlen(s) + 1)) {
	  
	  if (np->right != NULL)
		np = bst_find(s, np->right);
	}
	
	return (np);
  }

  return (NULL);
}

void
bst_insert(const char *s, BSTREE *tp)
{
  bst_node *np, *new;

  np = bst_find(s, tp->root);

  new = bst_mknode(s);

  if (np != NULL) {
	if (0 == strncmp(s, np->node, strlen(s) + 1) ||
		0 > strncmp(s, np->node, strlen(s) + 1)) {
	  np->left = new;
	} else {
	  np->right = new;
	}
  } else {
	tp->root = new;
  }
}

void
bst_free(bst_node *np)
{
  if (np != NULL) {

	if (np->left != NULL)
	  bst_free(np->left);

	if (np->right != NULL)
	  bst_free(np->right);

	free(np);
	return;
  }
}

void
bst_proc(bst_node *n, void (*func_p) (const char *s))
{
    bst_node *np;

	if (n && func_p) {
	  
	  np = n;
	  
	  if (np) {
		
		func_p(np->node);
		
		if (np->left)
		  bst_proc(np->left, func_p);
		if (np->right)
		  bst_proc(np->right, func_p);
	  }
	}
}
