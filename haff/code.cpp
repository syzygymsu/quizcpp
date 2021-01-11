#include "make_tree.h"
#include "tree.h"
#include <stdlib.h>
#include <assert.h>
#include <cstdio>

struct Buf {
	int counter;
	int byte;
	FILE* f;
};

struct List5 {
	int nomer;
	char* mass;
	List5 *next;
};


static void FilePrintZagolovok(int* mass, FILE* f, int size)
{
	fwrite(mass, 4, size, f);
}

static void addnextL5(List5* root, List5* newelem)
{
	// if (root->next != NULL) { root->next->prev = newelem; }
	// newelem->prev = root;
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
	char a[256]; // why size == 256
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
	// 2 simulate end of array
	mass[i] = 2;
	c1 = (List5*)malloc(sizeof(List5));
	assert(c1);
	c1->next = nullptr;
	c1->mass = mass;
	c1->nomer = pos->value.nomer;
	addnextL5(root, c1);

}

static List5* MakeList5(TreeNode* rootTree)
{
	List5* root;
	root = (List5*)malloc(sizeof(List5));
	assert(root);
	root->next = nullptr;
	root->nomer = 999;
	Left_Right2(rootTree, func, root);
	return root;
}


static void MakeMass(const char* t1, int* numb, int size)
{
	//clean Mass
	for (int i = 0; i < size; i++)
	{
		numb[i] = 0;
	}

	FILE* file;

	if ((file = fopen(t1, "r")) == NULL)
	{
		perror(t1);
		return;
	}
	//pods4et
	for (;;)
	{
		int c = getc(file);
		if (c == EOF) break;
		(numb[c])++;
	}
	fclose(file);

}


static void addBit(Buf* buffer, int symb) {
	if (symb == 0)
	{
		buffer->byte = buffer->byte << 1;
	}
	else
	{
		buffer->byte = (((buffer->byte) << 1) | 1);
	}
	buffer->counter++;
	if (buffer->counter == 8)
	{
		fwrite(&buffer->byte, 1, 1, buffer->f);
		buffer->counter = 0;
		buffer->byte = 0;
	}
}

static char* Search(int c, List5* root)
{
	List5* s;
	List5* cur;
	cur = root->next;
	while (cur->nomer != c) cur = cur->next;
	s = cur;
	return s->mass;
}

static void FileOut(List5* root5, const char* in, const char* out, int* mass, int size)
{
	int c;
	char* s;
	FILE* filein;
	Buf buffer;
	if ((filein = fopen(in, "rb")) == NULL)
	{
		perror(in);
		return;
	}
	if ((buffer.f = fopen(out, "wb")) == NULL)
	{
		perror(out);
		fclose(filein);
		return;
	}
	buffer.byte = 0;
	buffer.counter = 0;

	FilePrintZagolovok(mass, buffer.f, size);

	for (;;)
	{
		c = getc(filein);
		if (c == EOF) break;
		s = Search(c, root5);
		while (*s != 2) // what is 2?
		{
			addBit(&buffer, *s);
			s++;
		}
	}
	fclose(filein);
	while (buffer.counter != 0)
	{
		addBit(&buffer, 0);
	}
	fclose(buffer.f);
}

void FileCode(const char* in, const char* out)
{
	constexpr int size = 256;
	int numb[size];
	MakeMass(in, numb, size);
	TreeNode* rootTree = MakeTreeFromArray(numb, size);
	if (rootTree != NULL)
	{
		List5* root5 = MakeList5(rootTree);
		FileOut(root5, in, out, numb, size);
		DelTree(rootTree);
	}
	else
	{
		FileOut(nullptr, in, out, numb, size);
		//printf ("Error on open file or file is empty ");
	}
}
