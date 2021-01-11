#ifndef __BIBLIO_H__
#define __BIBLIO_H__

typedef struct Ls {
	int kolvo,nomer;
} Type1;


typedef struct Tr {
		Type1 value;
		struct Tr *prev, *left, *right;
} TreeNode;

TreeNode* CreateNote1(int,int);
TreeNode *AddLeft(TreeNode * , TreeNode *);
TreeNode *AddRight(TreeNode * , TreeNode *);
TreeNode* GoLeft(TreeNode* );
TreeNode* GoRight(TreeNode* );
void PrintTree(TreeNode *);
void Left_Right1(TreeNode *, void(*f)(TreeNode *));
void Down_Up(TreeNode *pos, void(*f)(TreeNode *));
void DelTree(TreeNode * );

TreeNode* MakeTreeFromArray(int* numb);

void DecodeFileOut(char*,char*);
void FileCode(char*,char*);

#endif // !__BIBLIO_H__
