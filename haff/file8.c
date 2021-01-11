#include "Biblio.h"

static void addnextL5(List5* root, List5* newelem)
{
	if (root->next != NULL) { root->next->prev = newelem; }
	newelem->prev = root;
	newelem->next = root->next;
	root->next = newelem;
}


static void Left_Right2(TreeNode* pos, void(*f)(TreeNode*, List5*), List5* root)
{
	if (pos == NULL) return;
	Left_Right2(GoLeft(pos), f, root);
	f(pos, root);
	Left_Right2(GoRight(pos), f, root);
}


static void func(TreeNode* pos, List5* root)
{
	char a[256];
	List5* c1;
	char* mass;
	TreeNode* b;
	int i = 0, j;
	if (pos->left || pos->right) return;
	if (pos->prev == NULL) { a[0] = 1; i++; }
	b = pos;
	while (b->prev != NULL)
	{

		if (b->prev->right == b) a[i] = 1;
		else a[i] = 0;
		i++;
		b = b->prev;
	}
	mass = (char*)malloc(i + 1);
	assert(mass);
	for (j = 0; j < i; j++)
	{
		mass[j] = a[i - j - 1];
	}
	mass[i] = 2;
	c1 = (List5*)malloc(sizeof(List5));
	assert(c1);
	c1->prev = c1->next = NULL;
	c1->mass = mass;
	c1->nomer = pos->value.nomer;
	addnextL5(root, c1);

}

List5* MakeList5(TreeNode* rootTree)
{
	List5* root;
	root = (List5*)malloc(sizeof(List5));
	assert(root);
	root->next = root->prev = NULL;
	root->nomer = 999;
	Left_Right2(rootTree, func, root);
	return root;
}
