#include "Biblio.h"
void MakeMass(char* t1, int* numb)
{
	FILE* file;
	int summ = 0, c, i;

	if ((file = fopen(t1, "r")) == NULL)
	{
		perror(t1);
		return;
	}
	//clean Mass
	for (i = 0; i < 256; i++)
	{
		numb[i] = 0;
	}
	//pods4et
	for (;;)
	{
		c = getc(file);
		if (c == EOF) break;
		summ++;
		(numb[c])++;
	}
	fclose(file);

}

List* ListMake(int* numb)
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

