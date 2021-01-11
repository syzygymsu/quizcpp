#include "Biblio.h"
int main(int argc, char* argv[])
{
	if (argc == 4)
	{
		FileCode(argv[1], argv[2]);
		EncodeFileOut(argv[3], argv[2]);
	}
	else { printf("Usage: %s filein fileout\n", argv[0]); }
	return 0;

}
