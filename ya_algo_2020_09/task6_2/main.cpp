// problems/F/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>

#include <assert.h>

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

int func(std::istream& f, std::ostream& out) {
    // ==== Loading ====
    int n, m, k;
    f >> n;
    f >> m;
    f >> k;
    if (k == 0) {
        out << '0' << std::endl;
        return 0;
    }
    cout << n << " " << m << " " << k << endl;
    vector<std::vector<int>> cols(n);
    for (int i = 0; i < k; ++i) {
        int x, y;
        f >> x;
        f >> y;
        cols.at(x).push_back(y);
    }
    for (auto& col : cols) {
        std::sort(col.begin(), col.end());
    }

    // ==== Init ====
    using Segment = pair<int, int>;
    vector<Segment> segments; // (begin, end)
    unordered_set<Segment*> unclosed; // segments to be closed
    for (int i = 0; i < k; ++i) {
        segments.push_back(make_pair(0, 0));
    }
    auto find_segment = [&](int target) {
        auto pp = partition_point(segments.begin(), segments.end(), [&](Segment& l){
            return (l.second <= target + 1) 
                && (l.first <= target);
        });
        assert(pp != segments.begin());
        --pp;
        return pp;
    };

    // ==== Process ====
    for (auto& col :cols) {
/*
        for (int y : col) {
            cout << y << " ";
        }
        cout << endl;
*/
        unordered_set<Segment*> unclosed_next;
        for (int point_idx = col.size() - 1; point_idx >= 0; --point_idx) {
            int top_y = col[point_idx];
            auto s = find_segment(top_y);

            // merge consequent points
            int bottom_y = top_y;
            while (point_idx > 0 
                    && col[point_idx-1] >= s->first
                    && col[point_idx-1] == bottom_y-1) {
                --point_idx;
                bottom_y = col[point_idx];
            }

            s->first = bottom_y;
            s->second = top_y + 1;
            unclosed.erase(&*s);
            unclosed_next.insert(&*s);
        }

        // close unclosed segments
        for(Segment* s : unclosed) {
            s->first = s->second;
        }
        unclosed = move(unclosed_next);
/*
        for (Segment& s : segments) {
            cout << "(" << s.first << "," << s.second << ") ";
        }
        cout << endl;
*/
    }

    int res = 0;
    for (Segment& s : segments) {
        if (s.first) ++res;
        if (s.second) ++res;
    }
    return res;
}


#include <chrono> 

void test(const std::string& filename, int expected) {
    std::ifstream f(filename);
    if (!f) {
        cerr << "File not found: " << filename << endl;
        return;
    }
    std::cout << "TESTING: " << filename << endl;
    // std::ofstream out("output.txt");
    auto start = std::chrono::high_resolution_clock::now();

    int res = func(f, std::cout);
    auto finish = std::chrono::high_resolution_clock::now();
    if (res != expected) {
        std::cout << "!!!!ERROR in test " + filename << ": expected " << expected << " but got " << res << std::endl;
        abort();
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
//    test("input30x30p2.txt", 57);
    test("input30.txt", 58);
    test("input10.txt", 19);
    test("inputdotslongdots.txt", 11);
    test("inputdots.txt", 10);
    test("inputdots2.txt", 10);
    test("input10kx10k.txt", 19997);
    test("input100kx100k.txt", 199997);
    test("input250kx250k.txt", 499997);
    return 0;
}
