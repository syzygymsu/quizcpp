#include "make_tree.h"
#include "tree.h"
#include <cstdio>
#include <vector>
#include <functional>

struct Buf {
	Buf() : counter(0), byte(0) {}
	void addBit(bool symb) {
		byte = (((byte) << 1) | (int)symb);
		counter++;
		if (counter == 8)
		{
			fwrite(&byte, 1, 1, f);
			counter = 0;
			byte = 0;
		}
	}

	void flush() {
		while (counter != 0)
		{
			addBit(0);
		}
	}
	FILE* f;
private:
	int counter;
	int byte;
};

struct LetterIndexToBoolSequence {
	LetterIndexToBoolSequence(int size) : map(size) {}
	void add(int nomer, std::vector<bool> mass) {
		map[nomer] = mass;
	}

	void foreach(int nomer, std::function<void(bool)> f) const {
		for (bool b : map[nomer]) {
			f(b);
		}
	}
private:
	std::vector<std::vector<bool>> map;
};


static void Left_RightChildrens(TreeNode* pos, std::function<void(TreeNode*, std::vector<bool>)> f, std::vector<bool> path)
{
	if (pos == NULL) return;
	if (!GoLeft(pos) && !GoRight(pos)) {
		f(pos, path);
	}
	else {
		path.push_back(false);
		Left_RightChildrens(GoLeft(pos), f, path);
		path.pop_back();
		path.push_back(true);
		Left_RightChildrens(GoRight(pos), f, path);
	}
}

static void FilePrintZagolovok(int* mass, FILE* f, int size)
{
	fwrite(mass, 4, size, f);
}

struct Walker {
	Walker(LetterIndexToBoolSequence& _root) : root(_root) {}
	void operator()(TreeNode* node, std::vector<bool> path) {
		root.add(node->value.nomer, path);
	}
private:
	LetterIndexToBoolSequence& root;
};

static LetterIndexToBoolSequence MakeLetterIndexToBoolSequence(TreeNode* rootTree, int size)
{
	LetterIndexToBoolSequence root(size);
	Walker walker(root);
	Left_RightChildrens(rootTree, walker, {});
	return root;
}

static void MakeMass(const char* t1, int* numb, int size)
{
	//clean
	for (int i = 0; i < size; i++)
	{
		numb[i] = 0;
	}

	FILE* file;

	if ((file = fopen(t1, "r")) == NULL)
	{
		perror(t1);
		return;
	}
	// counting
	for (;;)
	{
		int c = getc(file);
		if (c == EOF) break;
		(numb[c])++;
	}
	fclose(file);

}

static void FileOut(const LetterIndexToBoolSequence* root, const char* in, const char* out, int* mass, int size)
{
	FILE* filein;
	Buf buffer;
	if ((filein = fopen(in, "rb")) == NULL)
	{
		perror(in);
		return;
	}
	if ((buffer.f = fopen(out, "wb")) == NULL)
	{
		perror(out);
		fclose(filein);
		return;
	}

	FilePrintZagolovok(mass, buffer.f, size);

	for (;;)
	{
		int c = getc(filein);
		if (c == EOF) break;
		root->foreach(c, [&buffer](bool b) { buffer.addBit(b); });		
	}
	fclose(filein);
	buffer.flush();
	fclose(buffer.f);
}

void FileCode(const char* in, const char* out)
{
	constexpr int size = 256;
	int numb[size];
	MakeMass(in, numb, size);
	TreeNode* rootTree = MakeTreeFromArray(numb, size);
	if (rootTree != nullptr)
	{
		LetterIndexToBoolSequence root5 = MakeLetterIndexToBoolSequence(rootTree, size);
		FileOut(&root5, in, out, numb, size);
		DelTree(rootTree);
	}
	else
	{
		FileOut(nullptr, in, out, numb, size);
	}
}
