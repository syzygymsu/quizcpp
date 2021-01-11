#include "Biblio.h"
static void addBit(Buf* buffer, int symb){
    if(symb == 0)
    {
	buffer->byte = buffer->byte<<1;
	
    } 
    else 
    {
	buffer->byte = (((buffer->byte)<<1)|1);
	}
	buffer->counter++;
    if (buffer->counter == 8 ) 
    {
	fwrite(&buffer->byte, 1, 1 , buffer->f);
	buffer->counter = 0;
	buffer->byte = 0;
    }
}

static char * Search(int c, List5 *root)
{
	List5 *s;
	List5 *cur;
	cur=root->next;
	while (cur->nomer!=c) cur=cur->next;
	s=cur;
	return s->mass;
}

static void FileOut(List5 * root5, char *t1, char *t2, int *mass)
{	
	int c;
	char * s;
	int i=0;
	FILE *filein;//,*fileout;
	Buf *buffer;
	buffer=(Buf*)malloc(sizeof(Buf));
	if ((filein = fopen (t1,"rb"))== NULL)
	{
	   perror (t2);
	   return;
	}
	if ((buffer->f = fopen (t2,"wb"))== NULL)
	{
	   perror (t2);
	   fclose(filein);
	   return;
	}
	buffer->byte=0;
	buffer->counter=0;

	FilePrintZagolovok(mass,buffer->f);

	for(;;)
	{
		c = getc(filein);
		if(c==EOF) break;
		s=Search(c,root5);
		while (s[i] != 2)
		{
	       		addBit(buffer, *s);
				s++;
		}
	}
	fclose(filein);
	while(buffer->counter!=0)
	{
		addBit(buffer,0);
	}
	fclose(buffer->f);
	free(buffer);
}

void FileCode(char  *t1, char  *t2)
{
	TreeNode * rootTree=NULL;
	List *root;
	List5 *root5=NULL;
	int numb[257];
	MakeMass(t1,numb);
	root=ListMake(numb);
	//PrintList(root);
	if (root->next!=NULL)
	{
		rootTree=MakeTree(root);
		//PrintTree(rootTree);
		root5=MakeList5(rootTree);
		FileOut(root5,t1,t2,numb);
		DelTree(rootTree);
	}
	else 
	{	
		FileOut(root5,t1,t2,numb);
		//printf ("Error on open file or file is empty ");
	}
}

