#include "tree.h"
#include <cstdio>

static void PrintElem(TreeNode* a)
{
	if (a == nullptr) std::printf("ERROR");
	else std::printf("%d %d\n", a->value.kolvo, a->value.nomer);
}

void PrintTree(TreeNode* root)
{
	Down_Up(root, PrintElem);
}
