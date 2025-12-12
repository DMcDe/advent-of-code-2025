#include <iostream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>

long long numPaths(std::unordered_set<std::string> &vis, std::unordered_map<std::string, std::unordered_set<std::string>> &adj, 
    std::unordered_map<std::string, int> &memo, std::string cur, std::string trg, long long cnt) {
    if (cur == trg) {
        for (auto s : vis) std::cout << s << " ";
        std::cout << "\n";
        return 1 + cnt;
    }
    if (memo.contains(cur)) return cnt + memo[cur];
    for (auto s : adj[cur]) {
        long long before = cnt;
        if (!vis.contains(s)) {
            vis.insert(s);
            cnt = numPaths(vis, adj, memo, s, trg, cnt);
            vis.erase(s);
        }
        memo[s] = cnt - before;
    }
    return cnt;
}

int partA(std::unordered_map<std::string, std::unordered_set<std::string>> &adj) {
    std::unordered_set<std::string> vis;
    std::unordered_map<std::string, int> memo;
    vis.insert("you");
    return numPaths(vis, adj, memo, "you", "out", 0);    
}

int partB(std::unordered_map<std::string, std::unordered_set<std::string>> &adj) {
    std::unordered_set<std::string> vis;
    std::unordered_map<std::string, int> memo;

    vis.insert("svr");
    long long SVRtoDAC = numPaths(vis, adj, memo, "svr", "dac", 0LL);
    memo.clear();
    vis.clear();
    vis.insert("dac");
    long long DACtoFFT = numPaths(vis, adj, memo, "dac", "fft", 0LL);
    memo.clear();
    vis.clear();
    vis.insert("fft");
    long long FFTtoOUT = numPaths(vis, adj, memo, "fft", "out", 0LL);
    memo.clear();
    vis.clear();
    
    vis.insert("svr");
    long long SVRtoFFT = numPaths(vis, adj, memo, "svr", "fft", 0LL);
    memo.clear();
    vis.clear();
    vis.insert("fft");
    long long FFTtoDAC = numPaths(vis, adj, memo, "fft", "dac", 0LL);
    memo.clear();
    vis.clear();
    vis.insert("dac");
    long long DACtoOUT = numPaths(vis, adj, memo, "dac", "out", 0LL);

    long long fftFirst = SVRtoDAC * DACtoFFT * FFTtoOUT;
    long long dacFirst = SVRtoFFT * FFTtoDAC * DACtoOUT;
    return fftFirst + dacFirst;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::unordered_map<std::string, std::unordered_set<std::string>> adj;

    std::string str;

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