#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    char ch;
    int n;

    int num = 50;
    int count = 0;

    while (std::cin >> ch >> n) {
        ch == 'R' ? num = (num + n) % 100 : num = (num - n) % 100;
        if (num < 0) num += 100;
        
        if (num == 0) count++;
    }

    std::cout << "Day 1 part A: " << count << "\n";

    return 0;
}