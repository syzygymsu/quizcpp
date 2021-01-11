#include "Biblio.h"
#include <stdio.h>


static void FileReadZagolovok(int* mass, FILE* f)
{
	fread(mass, 4, 256, f);
}


static void Convert8(char* buf, int b)
{
	int i, a;
	for (i = 0; i < 8; i++)
	{
		a = 8 - i - 1;
		buf[a] = ((b >> i) & 1);
	}
}

static int Summ(int* mass)
{
	int i, a = 0;
	for (i = 0; i < 256; i++) a += mass[i];
	return a;
}
static void Encode(TreeNode* root, FILE* fileout, FILE* filein, int summ)
{
	char mass[8];
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
				fclose(filein);
				fclose(fileout);
				return;
			}
			Convert8(mass, b);
		}

		if (mass[cnt] == 0) 	list = GoLeft(list);
		else 			list = GoRight(list);

		if (!(GoLeft(list) || GoRight(list)))
		{
			fwrite(&list->value.nomer, 1, 1, fileout);
			list = root;
			i++;
			//break;
		}

		/*if(mass[cnt]==0) list=GoLeft(list);
		else list=GoRight(list);*/


		cnt++;
	}
}

void DecodeFileOut(char* t1, char* t2)
{
	int summ;
	int mass[256];
	FILE* fileout, * filein;
	TreeNode* rootTree = NULL;
	if ((fileout = fopen(t1, "w")) == NULL)
	{
		perror(t1);
		return;
	}
	if ((filein = fopen(t2, "r")) == NULL)
	{
		perror(t2);
		fclose(fileout);
		return;
	}

	FileReadZagolovok(mass, filein);

	rootTree = MakeTreeFromArray(mass);
	//PrintTree(rootTree);
	summ = Summ(mass);
	//printf("%d\n",summ);
	Encode(rootTree, fileout, filein, summ);

	fclose(filein);
	fclose(fileout);
}
