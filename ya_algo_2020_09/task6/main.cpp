// problems/F/

#include <iostream>
#include <fstream>
// #include <string>
#include <vector>
#include <algorithm>
// #include <cstring>

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
//    for (const auto& row : rows) {
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
    std::vector<std::vector<int>> rows(m, { n + 1 });
    //for (auto& row : rows) {
    //    // row.reserve(n + 1);
    //    row.push_back(n + 1);
    //}
    std::vector<int> cols(n, 0);
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
    //print(cols);
    //std::cout << endl;

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
                ++iterCount;
                break;
            }
        }
        int localNonZero = cols[fisrtNonZeroCol];
        // std::cout << full_rows << endl<<endl;
        for (int j = full_rows; j < m; ++j) {
            auto& row = rows[j];
            // print(positions);
            if (color) {
                /// if (positions[j + 1])
                while (positions[j + 1] == row.back() && positions[j + 1] < positions[j]) {
                    positions[j + 1] = row.back() + 1;
                    --cols[row.back()];
                    if (row.back() == fisrtNonZeroCol) {
                        --localNonZero;
                    }
                    row.pop_back();
                    // std::cout << "in color ";
                     ++iterCount;
                }
                //for (int i = fisrtNonZeroCol; i < n; ++i) {
                //    if (cols[i] > 0) {
                //        // ++iterCount;
                //        fisrtNonZeroCol = i;
                //        break;
                //    }
                //}
                ++iterCount;
                if (localNonZero == 0) {
                    // std::cout  << "break " << j << " " << color << " " << "fisrtNonZeroCol " << fisrtNonZeroCol << " " << positions[j + 1];
                    break;
                }
                // std::cout << std::endl << "j " << j << " " << color << " " << "fisrtNonZeroCol " << fisrtNonZeroCol << " " << positions[j + 1];

                // print(rows);
            }
            else {
                if (row.back() > positions[j]) {
                    ++iterCount;
                    // std::cout << "more " << row.back() << " " << j << " " << positions[j]  << " " << positions[j + 1] << " " << localNonZero << std::endl;
                    positions[j + 1] = positions[j];
                }
                else {
                    ++iterCount;
                    if (row.back() > fisrtNonZeroCol) {
                        positions[j + 1] = row.back();
                    } else if (row.back() == fisrtNonZeroCol) {
                        --localNonZero;
                        if (localNonZero == 0) {
                            // std::cout << "fill" << std::endl;
                            std::fill(positions.begin() + j + 1, positions.end(), fisrtNonZeroCol);
                            break;
                        }
                        positions[j + 1] = fisrtNonZeroCol;
                    }
                    
                    // std::cout << "less " << "j " << j << " " << color << " " << "fisrtNonZeroCol " << fisrtNonZeroCol << " " << positions[j + 1] << std::endl;
                    // positions[j + 1] = row.back();
                }
            }
            if (positions[j + 1] == n + 1) {
                // std::cout << "full" << endl;
                full_rows = j + 1;
            }
            else if (positions[j + 1] == 0) {
                // std::cout << "break " << whileCount << " j " << j << " full_rows " << full_rows << " iterCount " << iterCount << endl;
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
    std::ifstream f("input10k.txt");
    std::ofstream out("output.txt");
    auto start = std::chrono::high_resolution_clock::now();
    func(f, out);
    // func(std::cin, std::cout);

    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(finish - start).count();
    return 0;
}
