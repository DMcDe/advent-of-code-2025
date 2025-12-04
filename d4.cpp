#include <iostream>
#include <vector>

const std::vector<std::pair<int, int>> neighbors = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
};

int partA(const std::vector<std::vector<char>> &map) {
    int m = map.size();
    int n = map[0].size();

    int res = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int empty = 0;
            for (auto p : neighbors) {
                if (map[i][j] == '@' && 
                    (i + p.first < 0 || i + p.first >= m || j + p.second < 0 || j + p.second >= n || map[i + p.first][j + p.second] != '@')) empty++;
            }
            if (empty > 4) res++;
        }
    }

    return res;
}

int partBHelper(std::vector<std::vector<char>> &map) {
    int m = map.size();
    int n = map[0].size();

    int res = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int empty = 0;
            for (auto p : neighbors) {
                if (map[i][j] == '@' && 
                    (i + p.first < 0 || i + p.first >= m || j + p.second < 0 || j + p.second >= n || map[i + p.first][j + p.second] != '@')) {
                        empty++;
                    }
            }
            if (empty > 4) {
                res++;
                map[i][j] = '.';
            }
        }
    }

    return res;
}

int partB(std::vector<std::vector<char>> &map) {
    int res = 0;
    int removed = partBHelper(map);

    while (removed > 0) {
        res += removed;
        removed = partBHelper(map);
    }

    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string line;
    std::vector<std::vector<char>> map;

    while (std::getline(std::cin, line)) {
        std::vector<char> vec;
        for (char c : line) vec.push_back(c);
        map.push_back(vec);
    }

    std::cout << "Part A solution: " << partA(map) << "\n";
    std::cout << "Part B solution: " << partB(map) << "\n";

    return 0;
}