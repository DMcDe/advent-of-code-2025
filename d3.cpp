#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int partA(std::vector<std::string> &banks) {
    int total = 0;

    for (std::string s : banks) {
        int fst = 0;
        int snd = 0;

        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            int n = c - '0';

            if (n > fst && i != s.size() - 1) {
                fst = n;
                snd = 0;
            } else if (n > snd || (n > fst && i == s.size() - 1)) {
                snd = n;
            }
        }

        total += fst * 10 + snd;
    }

    return total;
}

long long partB(std::vector<std::string> &banks) {
    long long total = 0;
    const int NUM_CELLS = 12;
    
    for (std::string s : banks) {
        std::vector<int> nums(NUM_CELLS, 0);

        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            int n = c - '0';

            for (int j = 0; j < NUM_CELLS; j++) {
                // Want to consider cells [0, s.size() - (NUM_CELLS - j)]
                if (i <= s.size() - (NUM_CELLS - j)) {
                    if (n > nums[j]) {
                        nums[j] = n;
                        std::fill(nums.begin() + j + 1, nums.end(), 0);
                        break;
                    }
                }
            }
        }

        long long joltage = 0;

        for (int j = 0; j < NUM_CELLS; j++) {
            joltage += (nums[j] * static_cast<long long>(powl(10, NUM_CELLS - j - 1)));
        }

        total += joltage;
    }

    return total;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str;
    std::vector<std::string> input;

    while (getline(std::cin, str)) {
        input.push_back(str);
    }

    std::cout << "Part A solution: " << partA(input) << "\n";
    std::cout << "Part B solution: " << partB(input) << "\n";

    return 0;
}