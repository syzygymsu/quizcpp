#include "tree.h"
#include <queue>

TreeNode* MakeTreeFromArray(int* numb, int size) {
	auto cmp = [](TreeNode* left, TreeNode* right) { return right->value.kolvo < left->value.kolvo; };
	std::priority_queue<TreeNode*, std::vector<TreeNode*>, decltype(cmp) > q2;
	for (int i = 0; i < size; i++)
	{
		if (numb[i] > 0)
		{
			int k = numb[i];
			TreeNode* c1 = CreateNote1(k, i);
			q2.push(c1);
		}
	}
	if (q2.size() == 1) {
		// 
		TreeNode* root = q2.top();
		TreeNode* c1 = CreateNote1(root->value.kolvo, root->value.nomer);
		AddLeft(c1, root);
	}
	while (q2.size() > 1)
	{
		TreeNode* a = q2.top();
		q2.pop();
		TreeNode* b = q2.top();
		q2.pop();
		TreeNode* c1 = CreateNote1(a->value.kolvo + b->value.kolvo, 0);
		AddLeft(a, c1);
		AddRight(b, c1);
		q2.push(c1);
	}
	TreeNode* rootTree = nullptr;
	if (!q2.empty()) {
		rootTree = q2.top();
		q2.pop();
	}
	return rootTree;
}
