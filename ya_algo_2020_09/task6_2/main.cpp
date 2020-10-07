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
    std::cout << "[";
    for (const auto& row : rows) {
        print(row);
    }
    std::cout << "]" << std::endl;
}

int func_good(std::istream& f, std::ostream& out) {
    int n, m, k;
    f >> n;
    f >> m;
    f >> k;
    if (k == 0) {
        out << '0' << std::endl;
        return 0;
    }
    std::vector<std::vector<int>> rows(m, { n + 1 });
    std::vector<int> cols(n + 1, 0);
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
                    }
                    else if (row.back() == fisrtNonZeroCol) {
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
    // std::cout << "iterCount " << iterCount << " iteration " << iteration << std::endl;
    // out << iteration << std::endl;
    return iteration;
}


int func(std::istream& f, std::ostream& out) {
    int n, m, k;
    f >> n;
    f >> m;
    f >> k;
    if (k == 0) {
        out << '0' << std::endl;
        return 0;
    }
    std::vector<std::vector<int>> rows(m);
    std::vector<std::vector<int>> cols(m);

    std::vector<int> colsx(n + 1, 0);

    for (int i = 0; i < k; ++i) {
        int x, y;
        f >> x;
        f >> y;
        int temp = n - 1 - x;
        rows[y].push_back(temp);
        cols[temp].push_back(y);
        ++colsx[temp];
    }
    for (auto& row : rows) {
        std::sort(row.begin(), row.end(), std::greater<int>());
    }

    for (auto& col : cols) {
        std::sort(col.begin(), col.end(), std::greater<int>());
    }
    // print(cols_q);
    bool color = !rows[0].empty() && rows[0].back() == 0;
    int full_rows = 0;
    std::vector<int> positions(m + 1, 0);
    positions[0] = n;
    int iteration = 0;
    int iterCount = 0;
    int fisrtNonZeroCol = 0;
    while (full_rows < m) {
        // std::cout << "while " << full_rows <<" " << iteration << std::endl;
        for (int i = fisrtNonZeroCol; i < n; ++i) {
            if (colsx[i] > 0) {
                fisrtNonZeroCol = i;
                break;
                // ++iterCount;
            }
        }
        int localNonZero = colsx[fisrtNonZeroCol];
        for (int j = full_rows; j < m; ++j) {
            // std::cout << "for " << j << std::endl;

            auto& row = rows[j];
            if (color) {
                // std::cout << "color " << j << std::endl;

                if (row.empty()) {
                    break;
                }
                int x = row.back();
                int pos = positions[j + 1];
                if (x == pos) {
                    while (pos == x && x < positions[j]) {
                        positions[j + 1] = x + 1;
                        pos = x + 1;
                        --colsx[x];
                        if (x == fisrtNonZeroCol) {
                            --localNonZero;
                        }
                        // cout << "in color " << iterCount << endl;
                        row.pop_back();
                        cols[x].pop_back();
                        ++iterCount;
                        if (row.empty()) {
                            break;
                        }
                        x = row.back();
                    }
                    ++iterCount;
                    if (localNonZero == 0) {
                        break;
                    }
                }
                else {
                    //auto& yvec = cols[positions[j + 1]];
                    //std::cout << "in color else " << j << " " << yvec.back() << endl;

                    //if (yvec.empty()) {
                    //    std::cout << "strange" << endl;
                    //    break;
                    //}
                    //j = yvec.back();
                }
                // cout << "skip color " << iterCount << endl;
            }
            else {
                // std::cout << "non color " << j << std::endl;

                ++iterCount;
                if (row.empty() || row.back() > positions[j]) {
                    positions[j + 1] = positions[j];
                }
                else {
                    if (row.back() > fisrtNonZeroCol) {
                        // std::cout << "less1 " << iterCount <<" " << localNonZero << std::endl;
                        positions[j + 1] = row.back();
                    }
                    else if (row.back() == fisrtNonZeroCol) {
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
            // std::cout << "pre full " << positions[j + 1]  << " "<< j << std::endl;
            // print(positions);
            if (positions[j + 1] >= n) {
                // std::cout << "full " << j << std::endl;
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
    // std::cout << "iterCount " << iterCount << " iteration " << iteration << std::endl;
    // out << iteration << std::endl;
    return iteration;
}


#include <chrono> 

void test(const std::string& filename, int expected) {
    std::ifstream f(filename);
    // std::ofstream out("output.txt");
    auto start = std::chrono::high_resolution_clock::now();

    int res = func(f, std::cout);
    auto finish = std::chrono::high_resolution_clock::now();
    if (res != expected) {
        std::cout << "!!!!ERROR in test " + filename << " " << res << std::endl;
    }
    else {
        std::cout << filename << " OK " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << std::endl;
    }
}

int main() {

    test("input1.txt", 1);
    test("input1dot.txt", 2);
    test("input1dot2.txt", 1);
    test("input2.txt", 2);
    test("input3.txt", 3);
    test("input30x30.txt", 57);
    test("input30x30p.txt", 57);
    test("input30.txt", 58);
    test("input10.txt", 19);
    test("inputdotslongdots.txt", 11);
    test("inputdots.txt", 10);
    test("inputdots2.txt", 10);
    // test("input10kx10k.txt", 19997);
    return 0;
}
