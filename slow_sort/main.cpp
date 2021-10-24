#include <algorithm>
#include <iostream>
#include <vector>

void make_killer(int size, std::vector<int>& v) {
    int candidate = 0;
    int num_solid = 0;
    int gas = size - 1;

    std::vector<int> tmp(size);
    v.resize(size);

    for (int i = 0; i < size; ++i) {
        tmp[i] = i;
        v[i] = gas;
    }

    std::sort(tmp.begin(), tmp.end(), [&](int x, int y) {
        if (v[x] == gas && v[y] == gas) {
            if (x == candidate) v[x] = num_solid++;
            else v[y] = num_solid++;
        }

        if (v[x] == gas) candidate = x;
        else if (v[y] == gas) candidate = y;

        return v[x] < v[y];
    });
}

int main(int argc, char** argv) {
    int size = 300000;
    std::vector<int> v;
    make_killer(size, v);
    for (int i = 0; i < size; ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
    

    return 0;
}
