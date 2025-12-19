#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

long long partA(std::vector<std::pair<long long, long long>> &c) {
    long long res = 0;
    for (int i = 0; i < c.size(); i++) {
        for (int j = i + 1; j < c.size(); j++) {
            long long area = llabs((c[i].first - c[j].first + 1) * (c[i].second - c[j].second + 1));
            // std::cout << "Pairs: " << c[i].first << ", " << c[i].second << " & " << c[j].first << ", " << c[j].second << ". Area: " << area << "\n";
            res = std::max(area, res);
        }
    }

    return res;

}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::pair<long long, long long>> corners;

    std::string str;
    char comma;
    long long x, y;

    while (std::getline(std::cin, str)) {
        std::stringstream ss(str);
        ss >> x >> comma >> y;
        corners.emplace_back(x, y);
    }

    std::cout << "Part A solution: " << partA(corners) << "\n";

    return 0;
}