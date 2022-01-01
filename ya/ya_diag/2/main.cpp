#include <iostream>
#include <string>
#include <vector>

void read_color(std::vector<std::vector<char>>& field, int size, char color) {
    for (int i = 0; i < size; ++i) {
        int x, y;
        std::cin >> x >> y;
        field[x-1][y-1] = color;
    }
}

char reversed_color(char c) {
    if (c == 'b') {
        return 'w';
    }
    if (c == 'w') {
        return 'b';
    }
    return 'e';
}


bool can_beat(const std::vector<std::vector<char>>& field, char color) {
    const int h = field[0].size();
    const int w = field.size();
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            if (field[i][j] == color) {
                if (i - 2 >= 0) {
                    if (j - 2 >= 0) {
                        if (field[i - 2][j - 2] == 'e') {
                            if (field[i - 1][j - 1] == reversed_color(color)) {
                                return true;
                            }
                        }
                    }
                    if (j + 2 < h) {
                        if (field[i - 2][j + 2] == 'e') {
                            if (field[i - 1][j + 1] == reversed_color(color)) {
                                return true;
                            }
                        }
                    }
                }
                if (i + 2 < w) {
                    if (j - 2 >= 0) {
                        if (field[i + 2][j - 2] == 'e') {
                            if (field[i + 1][j - 1] == reversed_color(color)) {
                                return true;
                            }
                        }
                    }
                    if (j + 2 < h) {
                        if (field[i + 2][j + 2] == 'e') {
                            if (field[i + 1][j + 1] == reversed_color(color)) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}


int main() {
    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<char>> field(N, std::vector<char>(M, 'e'));
    int w;
    std::cin >> w;
    read_color(field, w, 'w');
    int b;
    std::cin >> b;
    read_color(field, b, 'b');
    std::string color_str;
    // std::getline(std::cin, color_str);
    std::cin >> color_str;
    char color = color_str[0];
    bool res = can_beat(field, color);
    if (res) {
        std::cout << "Yes" << std::endl;
    }
    else {
        std::cout << "No" << std::endl;
    }
    return 0;
}
