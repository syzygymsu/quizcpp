#include "Biblio.h"
int main(int argc, char* argv[])
{
	//if (argc == 4)
	//{
	//	FileCode(argv[1], argv[2]);
	//	DecodeFileOut(argv[3], argv[2]);
	//}
	//else { printf("Usage: %s filein fileout\n", argv[0]); }
	FileCode("2.txt", "4.txt");
	DecodeFileOut("1.out.txt", "4.txt");
	return 0;

}
