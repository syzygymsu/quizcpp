#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>

bool check(int * v) {
    int f[6];
    f[0] = v[0] + v[1] + v[2] + v[3];
    f[1] = v[3] + v[2] + v[6] + v[7];
    f[2] = v[4] + v[5] + v[6] + v[7];
    f[3] = v[0] + v[1] + v[4] + v[5];
    f[4] = v[5] + v[1] + v[2] + v[6];
    f[5] = v[0] + v[3] + v[4] + v[7];
    std::sort(f, f+6);
    for (int i = 1; i < 6; ++i) {
        if (f[i] != f[i - 1]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[])
{
    if (argc < 9) {
        printf("Usage: ./cube a b c d e f g h\n");
        printf("   b---c       \n");
        printf("  /|  /|       \n");
        printf(" a-+-d |       \n");
        printf(" | f-|-g       \n");
        printf(" |/  |/        \n");
        printf(" e---h         \n");
        return -1;
    }
    int arr[8];
    for (int i = 0; i < 8; ++i) {
        arr[i] = std::stoi(argv[i + 1]);
    }

    bool res = check(arr);
    if (res) {
        std::cout << "OK" << std::endl;
    }
    else {
        std::cout << "FAIL" << std::endl;
    }
    return 0;
}
