#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <queue>
#include <sstream>
#include <vector>

class UnionFind {  
public:
    std::vector<int> reps;

    UnionFind(int size) {
        reps.resize(size);
        std::iota(reps.begin(), reps.end(), 0);
    }

    int find(int node) {
        // Find the representative of the given node
        int n = reps[node];

        // If the representative of this node is not its own representative (base case), 
        // Recurse until you find the representative
        // Set the representative of all nodes away to the final/base case rep for path compression
        while (reps[n] != n) {
            return reps[node] = find(n);
        }

        return n;
    }

    bool merge(int n1, int n2) {
        int p1 = find(n1);
        int p2 = find(n2);

        if (p1 == p2) {}
        else if (p1 < p2) reps[p2] = p1;
        else reps[p1] = p2;

        for (int i = 1; i < reps.size(); i++) if (find(reps[i]) != find(reps[i - 1])) return false;
        return true;
    }
};

void solve(std::vector<std::vector<long long>> &locs) {
    std::priority_queue<std::pair<double, std::pair<int, int>>, std::vector<std::pair<double, std::pair<int, int>>>, 
    std::greater<std::pair<double, std::pair<int, int>>>> pq;
    UnionFind uf(locs.size());

    for (int i = 0; i < locs.size(); i++) {
        for (int j = i + 1; j < locs.size(); j++) {
            double dist = std::sqrt(std::pow(locs[i][0] - locs[j][0], 2) + std::pow(locs[i][1] - locs[j][1], 2) + std::pow(locs[i][2] - locs[j][2], 2));
            // std::cout << "Distance between " << i << " & " << j << ": " << dist << "\n";
            pq.emplace(dist, std::make_pair(i, j));
        }
    }

    // 1000 was specified by the problem
    for (int i = 0; i < 1000; i++) {
        auto closest_pair = pq.top();
        pq.pop();
        uf.merge(closest_pair.second.first, closest_pair.second.second);
    }

    std::vector<int> children(locs.size(), 0);
    for (int i = 0; i < locs.size(); i++) children[uf.find(i)]++;
    std::sort(children.begin(), children.end());

    std::cout << "Largest circuits after 1,000 merges have sizes " << children[locs.size() - 1] << ", " << children[locs.size() - 2] << ", " << children[locs.size() - 3] << "\n";

    std::cout << "Part A solution: " << children[locs.size() - 1] * children[locs.size() - 2] * children[locs.size() - 3] << "\n";

    while (true) {
        auto closest_pair = pq.top();
        pq.pop();
        if (uf.merge(closest_pair.second.first, closest_pair.second.second)) {
            std::cout << "The last two connected junctions had x-coordinates: " << locs[closest_pair.second.first][0] << " & " << locs[closest_pair.second.second][0] << "\n"; 
            std::cout << "Part B solution: " << locs[closest_pair.second.second][0] * locs[closest_pair.second.first][0] << "\n";
            return;
        }
    }
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::vector<long long>> locs;
    std::string str;
    long long x, y, z;
    char comma;
    while (std::getline(std::cin, str)) {
        std::stringstream ss(str);
        ss >> x >> comma >> y >> comma >> z;
        locs.push_back({x, y, z});
    }

    solve(locs);

    return 0;
}