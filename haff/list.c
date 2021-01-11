#include "Biblio.h"
#include <stdlib.h>
#include <assert.h>

typedef struct _List {
	TreeNode* value;
	struct _List* prev, * next;
} List;

static List* createnote(TreeNode* n)
{
	List* a;
	a = malloc(sizeof(List));
	assert(a);
	a->value = n;
	a->prev = NULL;
	a->next = NULL;
	return a;
}


static List* addnext(List* cur, List* newelem)
{
	if (cur->next != NULL) { cur->next->prev = newelem; }
	newelem->prev = cur;
	newelem->next = cur->next;
	cur->next = newelem;
	return newelem;
}


static List* delnext(List* cur)
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

static List* movenext(List* cur)
{
	assert(cur);
	return cur->next;
}

static List* moveprev(List* cur)
{
	assert(cur);
	return (cur->prev);
}

static int cmp(TreeNode* x1, TreeNode* x2)
{
	if (x1->value.kolvo < x2->value.kolvo) return -1;
	if (x1->value.kolvo == x2->value.kolvo) return 0;
	return 1;
}

static void BubbleSort(List* root, int(*sort)(TreeNode*, TreeNode*))
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


static TreeNode* MakeTree(List* root)
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
	assert(c);
	return c->value;
}

static List* ListMake(int* numb)
{
	List* list = NULL, * cc, * root;
	int  k = 1, i;
	TreeNode* c1 = NULL;


	root = createnote(c1);
	list = root;
	for (i = 0; i < 256; i++)
	{
		if (numb[i] > 0)
		{
			k = numb[i];
			c1 = CreateNote1(k, i);
			cc = createnote(c1);
			list = addnext(list, cc);
		}
	}
	return root;
}


TreeNode* MakeTreeFromArray(int* numb) {
	List* list = ListMake(numb);
	TreeNode* rootTree = NULL;
	if (list->next != NULL)
		rootTree = MakeTree(list);
	return rootTree;
}
