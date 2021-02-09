#include "hirsh.h"
#include "test.h"

int main()
{
	bool res = test(hirsh);
	if (!res) {
		return 1;
	}
	res = test(hirsh_extra_space);
	if (!res) {
		return 1;
	}
	return 0;
}
