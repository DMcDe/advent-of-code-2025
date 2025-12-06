#include <algorithm>
#include <iostream>
#include <vector>

#define MID(l, r) (l + r) / 2

std::vector<std::pair<long long, long long>> mergeRanges(std::vector<std::pair<long long, long long>> &ranges) {
    std::sort(ranges.begin(), ranges.end());

    // for (auto r : ranges) std::cout << r.first << " " << r.second << "\n";
    // std::cout << "---\n";

    std::vector<std::pair<long long, long long>> res;

    long long l = ranges[0].first;
    long long r = ranges[0].second;

    for (int i = 1; i < ranges.size(); i++) {
        if (ranges[i].first > r + 1) {
            res.emplace_back(l, r);
            l = ranges[i].first;
            r = ranges[i].second;
        } else {
            r = std::max(ranges[i].second, r);
        }
    }

    res.emplace_back(l, r);

    // for (auto r : res) std::cout << r.first << " " << r.second << "\n";

    return res;
}

bool searchRanges(const std::vector<std::pair<long long, long long>> &ranges, const long long q) {
    int l = 0, r = ranges.size();

    while (l < r) {
        if (ranges[MID(l, r)].first <= q && ranges[MID(l, r)].second >= q) return true;

        if (ranges[MID(l, r)].first > q) r = MID(l, r);
        else if (ranges[MID(l, r)].second < q) l = MID(l, r) + 1;
    }


    return false;
}

int partA(const std::vector<std::pair<long long, long long>> &ranges, const std::vector<long long> &queries) {
    int res = 0;

    for (auto q : queries) {
        if (searchRanges(ranges, q)) res++;
    }

    return res;
}

long long partB(const std::vector<std::pair<long long, long long>> &ranges) {
    long long res = 0;
    for (auto r : ranges) {
        res += (r.second - r.first + 1);
    }
    return res;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::pair<long long, long long>> ranges;
    std::vector<long long> queries;

    std::string str;

    // Read ranges
    while (std::getline(std::cin, str)) {
        if (str == "") break;

        size_t i = str.find("-");
        long long n1 = stoll(str.substr(0, i));
        long long n2 = stoll(str.substr(i + 1));

        ranges.emplace_back(n1, n2);
    }

    // Read individual IDs
    long long n;
    while (std::cin >> n) {
        queries.push_back(n);
    }

    // TODO: There's a bug in merged_ranges, since I get a different answer when I do/don't use it
    // TODO: There's also a bug in parsing?? since I'm still wrong when I use both ways and using linear search gives the same answer as binary
    // 680 too low, 897 too high
    std::vector<std::pair<long long, long long>> merged_ranges = mergeRanges(ranges);

    std::cout << "Part A solution: " << partA(merged_ranges, queries) << "\n";
    std::cout << "Part B solution: " << partB(merged_ranges) << "\n";

    return 0;
}