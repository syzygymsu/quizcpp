#include "make_tree.h"
#include "tree.h"
#include <cstdio>


static void FileReadZagolovok(int* mass, FILE* f, int size)
{
	fread(mass, 4, size, f);
}

static int getBit(int cnt, int b)
{
	return ((b >> (8 - cnt - 1)) & 1);
}

static int Summ(int* mass, int size)
{
	int summ = 0;
	for (int i = 0; i < size; i++) summ += mass[i];
	return summ;
}

static void Encode(TreeNode* root, FILE* fileout, FILE* filein, int summ)
{
	TreeNode* list;
	int cnt = 8, b, i;
	list = root;
	for (i = 0; i < summ;)
	{
		if (cnt == 8)
		{
			cnt = 0;
			b = getc(filein);
			if (b == EOF)
			{
				return;
			}
		}

		if (getBit(cnt, b) == 0) {
			list = GoLeft(list);
		}
		else {
			list = GoRight(list);
		}

		if (!(GoLeft(list) || GoRight(list)))
		{
			fwrite(&list->value.nomer, 1, 1, fileout);
			list = root;
			i++;
		}

		cnt++;
	}
}

void DecodeFileOut(const char* out, const char* in)
{
	constexpr int size = 256;
	int mass[size];
	FILE* fileout, * filein;
	if ((fileout = fopen(out, "w")) == NULL)
	{
		perror(out);
		return;
	}
	if ((filein = fopen(in, "r")) == NULL)
	{
		perror(in);
		fclose(fileout);
		return;
	}

	FileReadZagolovok(mass, filein, size);

	TreeNode* rootTree = MakeTreeFromArray(mass, size);
	//PrintTree(rootTree);
	int summ = Summ(mass, size);
	//printf("%d\n",summ);
	Encode(rootTree, fileout, filein, summ);

	fclose(filein);
	fclose(fileout);
}
