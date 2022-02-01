// https://habr.com/ru/post/648917/

#include <string>
#include <bitset>
#include <cassert>

size_t solution(const std::string& str) {
	std::bitset<26> chars;
	size_t result = 1;
	for (char c : str) {
		int ind = c - 'a';
		if (chars[ind]) {
			chars.reset();
			++result;
		}
		chars[ind] = true;
	}
	return result;
}

int main()
{
	assert(solution("world") == 1);
	assert(solution("worldw") == 2);
	assert(solution("dddd") == 4);
	assert(solution("cycle") == 2);
	assert(solution("abba") == 2);
	return 0;
}
