// problems/F/

// #include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// using namespace std;

//void print(const std::vector<int>& row) {
//    std::cout << "[";
//    for (int v : row) {
//        std::cout << v << " ";
//    }
//    std::cout << "]" << std::endl;
//}
//
//void print(const std::vector<std::vector<int>>& rows) {
//    for (auto row : rows) {
//        print(row);
//    }
//}

void func(std::istream& f, std::ostream& out) {
    int n, m, k;
    f >> n;
    f >> m;
    f >> k;
    if (k == 0) {
        out << '0' << std::endl;
        return;
    }
    std::vector<std::vector<int>> rows(m, {n+1});
    //for (auto& row : rows) {
    //    // row.reserve(n + 1);
    //    row.push_back(n + 1);
    //}
    for (int i = 0; i < k; ++i) {
        int x, y;
        f >> x;
        f >> y;
        rows[y].push_back(n - 1 - x);
    }

    for (auto& row : rows) {
        std::sort(row.begin(), row.end(), std::greater<int>());
    }

    bool color = rows[0].back() == 0;
    int full_rows = 0;
    std::vector<int> positions(m + 1, 0);
    positions[0] = n + 1;
    int iteration = 0;

    while (full_rows < m) {
        for (int j = full_rows; j < m; ++j) {
            auto& row = rows[j];
            if (color) {
                while (positions[j+1] == row.back() && positions[j+1] < positions[j]) {
                    positions[j+1] = row.back() + 1;
                    row.pop_back();
                }
            }
            else {
                if (row.back() > positions[j]) {
                    positions[j+1] = positions[j];
                }
                else {
                    positions[j+1] = row.back();
                }
            }
            if (positions[j+1] == n + 1) {
                full_rows = j + 1;
            }
            else if (positions[j+1] == 0) {
                break;
            }
        }

        color = !color;
        ++iteration;
    }
    if (color) {
        --iteration;
    }
    out << iteration << std::endl;
}

int main() {
    std::ifstream f("input.txt");
    std::ofstream out("output.txt");
    func(f, out);
    // func(std::cin, std::cout);
    return 0;
}
