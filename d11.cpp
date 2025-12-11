#include <iostream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>

int numPaths(std::unordered_set<std::string> &vis, std::unordered_map<std::string, std::unordered_set<std::string>> &adj, 
    std::unordered_map<std::string, int> &memo, std::string cur, int cnt, bool partB) {
    if (cur == "out") {
        for (auto s : vis) std::cout << s << " ";
        std::cout << "\n";

        // if (partB && (!vis.contains("fft") || !vis.contains("dac"))) return cnt;
        return 1 + cnt;
    }
    if (memo.contains(cur)) return cnt + memo[cur];
    for (auto s : adj[cur]) {
        int before = cnt;
        if (!vis.contains(s)) {
            vis.insert(s);
            cnt = numPaths(vis, adj, memo, s, cnt, partB);
            vis.erase(s);
        }
        memo[s] = cnt - before;
    }
    return cnt;
}

int partA(std::unordered_map<std::string, std::unordered_set<std::string>> &adj) {
    int res = 0;
    std::unordered_set<std::string> vis;
    std::unordered_map<std::string, int> memo;
    vis.insert("you");
    res = numPaths(vis, adj, memo, "you", 0, false);
    
    return res;
}

int partB(std::unordered_map<std::string, std::unordered_set<std::string>> &adj) {
    int res = 0;
    std::unordered_set<std::string> vis;
    std::unordered_map<std::string, int> memo;
    vis.insert("svr");
    res = numPaths(vis, adj, memo, "svr", 0, true);

    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::unordered_map<std::string, std::unordered_set<std::string>> adj;

    std::string str;
    std::cout << "Test\n";

    while (std::getline(std::cin, str)) {
        std::stringstream ss(str);

        std::string src, dst;
        ss >> src;
        src.pop_back();

        while (ss >> dst) {
            adj[src].insert(dst);
        }
    }

    std::cout << "Part A solution: " << partA(adj) << "\n";
    std::cout << "Part B solution: " << partB(adj) << "\n";

    return 0;
}