#include <climits>
#include <iostream>

int sign(int r) {
    if (r == 0) {
        return 0;
    }
    if (r > 0) {
        return 1;
    }
    if (r < 0) {
        return -1;
    }
    std::cout << "Error" << std::endl;
    return 0;
}

int sign2(int r) {
    return (r+1)/(abs(r)+1)+(r-1)/(abs(r)+1);
}

int sign3(int r) {
    return 2*r/(abs(r)+1);
}

int sign4(int r) {
    return r/(abs(r-1)+1)+r/(abs(r+1)+1);
}




void test_func(int(*f)(int), const std::string& name, int from, int to) {
    for (int i = from; i < to; ++i) {
        if (sign(i) != f(i)) {
            std::cout << "Error in " << name << " " << i << " " << sign(i) << " " << f(i) << std::endl;
        }
    }
    if (sign(to) != f(to)) {
        std::cout << "Error in " << name << " " << to << " " << sign(to) << " " << f(to) << std::endl;
    }
}

void test_big(int(*f)(int), const std::string& name) {
    test_func(f, name, INT_MIN, INT_MAX);
}

void test_small(int(*f)(int), const std::string& name) {
    test_func(f, name, -100000, 100000);
}


int main()
{
    std::cout << sign2(INT_MAX) << std::endl;
    test_small(sign2, "sign2");
    test_small(sign3, "sign3");
    test_small(sign4, "sign4");
    // test_big(sign2, "sign2");
    // test_big(sign4, "sign4");
	return 0;
}
