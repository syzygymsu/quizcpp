#include "make_tree.h"
#include "tree.h"
#include <cstdio>
#include <vector>

struct Buf {
	int counter;
	int byte;
	FILE* f;
};

struct List5 {
	List5(int size) : map(size) {}
	void add(int nomer, std::vector<char> mass) {
		map[nomer] = mass;
	}
	std::vector<char> get(int nomer) {
		return map[nomer];
	}
private:
	std::vector<std::vector<char>> map;
};


static void FilePrintZagolovok(int* mass, FILE* f, int size)
{
	fwrite(mass, 4, size, f);
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
	std::vector<char> mass(i); // TODO leak
	for (j = 0; j < i; j++)
	{
		mass[j] = a[i - j - 1];
	}
	root->add(pos->value.nomer, mass);
}

static List5 MakeList5(TreeNode* rootTree, int size)
{
	List5 root(size);
	Left_Right2(rootTree, func, &root);
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


static void FileOut(List5* root5, const char* in, const char* out, int* mass, int size)
{
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
		int c = getc(filein);
		if (c == EOF) break;
		std::vector vec = root5->get(c);
		for (char ch : vec) {
			addBit(&buffer, ch);
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
	if (rootTree != nullptr)
	{
		List5 root5 = MakeList5(rootTree, size);
		FileOut(&root5, in, out, numb, size);
		DelTree(rootTree);
	}
	else
	{
		FileOut(nullptr, in, out, numb, size);
		//printf ("Error on open file or file is empty ");
	}
}
