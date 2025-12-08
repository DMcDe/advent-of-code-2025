#include <iostream>
#include <vector>

int partA(std::vector<std::vector<char>> &map, int start) {
    int m = map.size();
    int n = map[0].size();
    int splits = 0;

    std::vector<bool> occ(n);
    occ[start] = true;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (map[i][j] == '^' && occ[j]) {
                splits++;
                occ[j] = false;
                if (j - 1 >= 0) occ[j - 1] = true;
                if (j + 1 < n) occ[j + 1] = true;
            }
        }
    }

    return splits;
}

long long partB(std::vector<std::vector<char>> &map, int start) {
    int m = map.size();
    int n = map[0].size();
    long long timelines = 1;

    std::vector<long long> tls(n, 0LL);
    tls[start] = 1LL;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (map[i][j] == '^') {
                timelines += tls[j];
                if (j - 1 >= 0) tls[j - 1] += tls[j];
                if (j + 1 < n) tls[j + 1] += tls[j];
                tls[j] = 0;
            }
        }
    }

    return timelines;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str;
    std::getline(std::cin, str);

    int start = str.find("S");

    std::vector<std::vector<char>> map;

    while (std::getline(std::cin, str)) {
        std::vector<char> line(str.size());
        std::copy(str.begin(), str.end(), line.begin());
        map.push_back(line);
    }

    std::cout << "Part A solution: " << partA(map, start) << "\n";
    std::cout << "Part B solution: " << partB(map, start) << "\n";

    return 0;
}