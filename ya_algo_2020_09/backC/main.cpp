// problems/B/

// #include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// using namespace std;


void func(std::istream& f, std::ostream& out) {
    int n, x, k;
    f >> n;
    f >> x;
    f >> k;
    std::vector<int> t_list(n);

    for (int i = 0; i < n; ++i) {
        f >> t_list[i];
    }

    std::sort(t_list.begin(), t_list.end());
    std::vector<int> t_unique;
    long t0 = 1e9 + 7;

    for (int t : t_list) {
        if (t > t0) {
            break;
        }
        int new_t = t % x;
        auto it = std::lower_bound(t_unique.begin(), t_unique.end(), new_t);
        if (it != t_unique.end() && *it == new_t) {
            continue;
        }
        t_unique.insert(it, new_t);
        k += t / x;
        int k1 = (k - 1) / t_unique.size();
        int k2 = (k - 1) % t_unique.size();
        t0 = (long)x * k1 + t_unique[k2];
    }
    out << t0 << std::endl;
}

int main() {
    std::ifstream f("input.txt");
    std::ofstream out("output.txt");
    func(f, out);
    // func(std::cin, std::cout);
    return 0;
}
