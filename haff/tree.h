#ifndef __TREE_H__
#define __TREE_H__

struct NodeValue {
	int kolvo, nomer;
};

struct TreeNode {
	NodeValue value;
	TreeNode* prev, * left, * right;
};

TreeNode* CreateNote1(int, int);
TreeNode* AddLeft(TreeNode*, TreeNode*);
TreeNode* AddRight(TreeNode*, TreeNode*);
TreeNode* GoLeft(TreeNode*);
TreeNode* GoRight(TreeNode*);
void PrintTree(TreeNode*);
void Left_Right1(TreeNode*, void(*f)(TreeNode*));
void Down_Up(TreeNode* pos, void(*f)(TreeNode*));
void DelTree(TreeNode*);

// TreeNode* MakeTreeFromArray(int* numb);

#endif // !__TREE_H__
