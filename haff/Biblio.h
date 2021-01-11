#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Ls{
	int kolvo,nomer;
} Type1;



typedef struct Tr {
		Type1 *value;
		struct Tr *prev, *left, *right;
} TreeNode;

typedef struct _List {
		TreeNode *value;
		struct _List *prev,*next;
} List;

typedef struct _List5 {
		int nomer;
		char *mass;
		struct _List5 *prev,*next;
} List5;


typedef struct _buf {
	int counter;
	int byte;
	FILE* f;
}Buf;
typedef struct _buf1 {
	int counter;
	int byte;
	FILE* f;
}Buf1;


TreeNode* CreateNote1(int,int);
TreeNode *AddLeft(TreeNode * , TreeNode *);
TreeNode *AddRight(TreeNode * , TreeNode *);
TreeNode* GoLeft(TreeNode* );
TreeNode* GoRight(TreeNode* );
void PrintElem(TreeNode *);
void PrintTree(TreeNode *);
void FreeSpase(TreeNode *);
void Left_Right1(TreeNode *, void(*f)(TreeNode *));
void Left_Right (TreeNode *,int *,int *);
void Down_Up(TreeNode *pos, void(*f)(TreeNode *));
void DelTree(TreeNode * );
int  cmp(TreeNode*,TreeNode*);


List *movenext(List *);
List *moveprev(List *);

List *createnote(TreeNode *);
List *addnext (List *, List * );
List *delnext (List *);
List *ListMake(int *);
void PrintList(List *);
void BubbleSort(List *root,int(*sort)(TreeNode*,TreeNode*));
TreeNode * MakeTree(List* root);


List5 *MakeList5(TreeNode *);
////void FileOut(List5*,char*,char*,int*);
void EncodeFileOut(char*,char*);
int PrintList5(List5*);

void FileCode(char*,char*);

void FileReadZagolovok(int*,FILE*);
void FilePrintZagolovok(int*,FILE*);

//void func(TreeNode *,List5 *);
void MakeMass(char*,int*);
// void addnextL5 (List5*, List5*);
