// problems/F/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void print(const std::vector<int>& row) {
    std::cout << "[";
    for (int v : row) {
        std::cout << v << " ";
    }
    std::cout << "]" << std::endl;
}

void print(const std::vector<std::vector<int>>& rows) {
    for (const auto& row : rows) {
        print(row);
    }
}

void func(std::istream& f, std::ostream& out) {
    int n, m, k;
    f >> n;
    f >> m;
    f >> k;
    if (k == 0) {
        out << '0' << std::endl;
        return;
    }
    std::vector<std::vector<int>> rows(m, { n + 1 });
    std::vector<int> cols(n+1, 0);
    for (int i = 0; i < k; ++i) {
        int x, y;
        f >> x;
        f >> y;
        int temp = n - 1 - x;
        rows[y].push_back(temp);
        ++cols[temp];
    }
    int fisrtNonZeroCol = 0;
    for (auto& row : rows) {
        std::sort(row.begin(), row.end(), std::greater<int>());
    }

    bool color = rows[0].back() == 0;
    int full_rows = 0;
    std::vector<int> positions(m + 1, 0);
    positions[0] = n + 1;
    int iteration = 0;
    int iterCount = 0;
    while (full_rows < m) {
        for (int i = fisrtNonZeroCol; i < n; ++i) {
            if (cols[i] > 0) {
                fisrtNonZeroCol = i;
                break;
                // ++iterCount;
            }
        }
        int localNonZero = cols[fisrtNonZeroCol];
        for (int j = full_rows; j < m; ++j) {
            auto& row = rows[j];
            if (color) {
                while (std::max(positions[j + 1], fisrtNonZeroCol) == row.back() && row.back() < positions[j]) {
                    positions[j + 1] = row.back() + 1;
                    --cols[row.back()];
                    if (row.back() == fisrtNonZeroCol) {
                        --localNonZero;
                    }
                    // cout << "in color " << iterCount << endl;
                    row.pop_back();
                    ++iterCount;
                }
                ++iterCount;
                if (localNonZero == 0) {
                    break;
                }
                // cout << "skip color " << iterCount << endl;
            }
            else {
                ++iterCount;
                if (row.back() > positions[j]) {
                    // std::cout << "more " << iterCount << " " << " localNonZero " << localNonZero << " " << fisrtNonZeroCol << std::endl;
                    positions[j + 1] = positions[j];
                }
                else {
                    if (row.back() > fisrtNonZeroCol) {
                        // std::cout << "less1 " << iterCount <<" " << localNonZero << std::endl;

                        positions[j + 1] = row.back();
                    } else if (row.back() == fisrtNonZeroCol) {
                        // std::cout << "less2 " << iterCount  << " " << localNonZero <<std::endl;

                        --localNonZero;
                        if (localNonZero == 0) {
                            positions[j + 1] = fisrtNonZeroCol;
                            break;
                        }
                        positions[j + 1] = fisrtNonZeroCol;
                    }
                }
            }
            if (positions[j + 1] == n + 1) {
                full_rows = j + 1;
            }
            else if (positions[j + 1] == fisrtNonZeroCol) {
                break;
            }
        }

        color = !color;
        ++iteration;
    }
    if (color) {
        --iteration;
    }
    std::cout << "iterCount " << iterCount << " iteration " << iteration << std::endl;
    out << iteration << std::endl;
}

#include <chrono> 
int main() {
    std::ifstream f("input30x30p.txt");
    std::ofstream out("output.txt");
    auto start = std::chrono::high_resolution_clock::now();
    func(f, out);
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    return 0;
}
