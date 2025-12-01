#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    char ch;
    int n;

    int num = 50;
    int count = 0;

    while (std::cin >> ch >> n) {
        std::cout << ch << " " << n << "\n";

        bool initially_zero = num == 0;
        bool changed_position = false;

        ch == 'R' ? num += n : num -= n;

        if (num == 100) {
            num = 0;
        }

        while (num > 99) {
            num -= 100;
            count++;
            changed_position = true;
        }

        while (num < 0) {
            num += 100;
            if (!initially_zero) count++;
            else {
                initially_zero = false;
                changed_position = true;
            }
        }

        if (num == 0 && !changed_position) count++;
    }

    std::cout << "Day 1 part B: " << count << "\n";

    return 0;
}