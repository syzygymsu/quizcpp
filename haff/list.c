#include "Biblio.h"

List* createnote(TreeNode* n)
{
	List* a;
	a = malloc(sizeof(List));
	a->value = n;
	a->prev = NULL;
	a->next = NULL;
	return a;
}


List* addnext(List* cur, List* newelem)
{
	if (cur->next != NULL) { cur->next->prev = newelem; }
	newelem->prev = cur;
	newelem->next = cur->next;
	cur->next = newelem;
	return newelem;
}


List* delnext(List* cur)
{
	List* b;
	assert(cur);
	assert(cur->next);
	b = cur->next;
	cur->next = b->next;
	if ((cur->next) != NULL) cur->next->prev = cur;
	b->prev = NULL;
	b->next = NULL;
	return b;
}

List* movenext(List* cur)
{
	assert(cur);
	return cur->next;
}

List* moveprev(List* cur)
{
	assert(cur);
	return (cur->prev);
}


void BubbleSort(List* root, int(*sort)(TreeNode*, TreeNode*))
{
	int p, s = 1;
	List* a;
	a = movenext(root);
	while (s)
	{
		s = 0;
		while ((movenext(a)) != NULL)
		{
			p = sort(a->value, a->next->value);
			if (p == 1)
			{
				a = addnext(moveprev(a), delnext(a));
				s = 1;
			}
			//			 print(root);
			if ((a = movenext(a)) == NULL) break;
		}
		a = movenext(root);
	}
}



TreeNode* MakeTree(List* root)
{
	List* a, * b, * c = NULL;
	TreeNode* c1;
	if (movenext(movenext(root)) == NULL)
	{

		c1 = CreateNote1(root->next->value->value.kolvo, root->next->value->value.nomer);
		AddLeft(c1, root->next->value);

		return root->next->value;
	}
	while (movenext(movenext(root)) != NULL)
	{

		BubbleSort(root, cmp);
		a = delnext(root);
		b = delnext(root);
		c1 = CreateNote1(a->value->value.kolvo + b->value->value.kolvo, 0);
		c = createnote(c1);
		AddLeft(a->value, c->value);
		AddRight(b->value, c->value);
		// clean memory here
		addnext(root, c);

	}

	return c->value;
}

