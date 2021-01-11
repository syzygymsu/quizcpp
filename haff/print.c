#include "Biblio.h"


void FileReadZagolovok(int* mass, FILE* f)
{
	fread(mass, 4, 256, f);
}


void FilePrintZagolovok(int* mass, FILE* f)
{
	fwrite(mass, 4, 256, f);
}

void PrintMass256(int* mass)
{
	int i;
	for (i = 0; i < 256; i++) printf("%d", mass[i]);
	printf("\n");
}


void PrintList(List* root)
{
	List* a;
	a = root;
	while ((a = movenext(a)) != NULL)
	{
		printf("%d %d\n", a->value->value.kolvo, a->value->value.nomer);
		//a=a->next;
	}
	printf("\n");
}

void PrintMass8(char* mass)
{
	int i;
	for (i = 0; i < 8; i++) printf("%d", mass[i]);
	printf("\n");
}

void PrintElem(TreeNode* a)
{
	if (a == NULL) printf("ERROR");
	else printf("%d %d\n", a->value.kolvo, a->value.nomer);
}

void PrintTree(TreeNode* root)
{
	TreeNode* a;
	assert(root);
	a = root;
	Down_Up(a, PrintElem);
}

