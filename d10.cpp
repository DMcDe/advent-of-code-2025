#include <iostream>
#include <sstream>
#include <vector>

/* Initialize min to num buttons

// For each button (i in 0 to n)
    // If state matches goal, update min and return
    // Recursion 1:
        // Update state to pressing it
        // Increment num presses
        // If num presses >= min, return without branching further
        // Else, continue with array of buttons starting at i + 1
    // Recursion 2:
        // Keep unpressed
        // Continue with array of buttons starting at i + 1

// Return min
*/
int singleLinePartA(std::vector<bool> &trg, std::vector<bool> &crr, std::vector<std::vector<int>> &btns, int idx, int min, int presses) {
    // If worse than min, return min
    if (presses >= min) return min;

    // If state matches goal, update min and return
    bool match = true;
    for (int i = 0; i < trg.size(); i++) {
        if (trg[i] != crr[i]) {
            match = false;
            break;
        }
    }
    if (match) return presses;

    // If out of buttons to toggle, return min
    if (idx >= btns.size()) return min;

    // Recursion 2: update state to pressing button
    std::vector<bool> prs(crr);
    for (int l : btns[idx]) {
        prs[l] = !crr[l];
    }
    
    // Recursion 1: continue to next button without pressing current
    return std::min(singleLinePartA(trg, crr, btns, idx + 1, min, presses), 
                    singleLinePartA(trg, prs, btns, idx + 1, min, presses + 1));
}

int singleLinePartB(std::vector<int> &trg, std::vector<int> &crr, std::vector<std::vector<int>> &btns, int min, int presses) {
    // If worse than min, return min
    if (presses >= min) return min;

    // If state matches goal, return presses
    bool match = true;
    for (int i= 0; i < trg.size(); i++) {
        if (trg[i] != crr[i]) {
            match = false;
            break;
        }
    }
    if (match) return presses;

    // Update state to pressing button
    int mn = min;
    bool overshot = false;
    for (int i = 0; i < btns.size(); i++) {
        for (int l : btns[i]) {
            // If overshot, can't be right -- don't bother exploring
            if (++crr[l] > trg[l]) overshot = true;
        }
        if (!overshot) mn = std::min(mn, singleLinePartB(trg, crr, btns, mn, presses + 1));
        for (int l : btns[i]) {
            --crr[l];
        }
    }

    return mn;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int partA = 0;
    int partB = 0;

    std::string str;
    char ch;
    int n;
    while (std::getline(std::cin, str)) {
        std::vector<bool> target;
        std::vector<std::vector<int>> buttons;
        std::vector<int> joltages;

        std::stringstream ss(str);
        ss >> ch;

        // Read in light target states
        while (ch != ']') {
            if (ch == '.') target.push_back(false);
            else if (ch == '#') target.push_back(true);
            ss >> ch;
        }

        // std::cout << "Num buttons: " << target.size() << "\n";

        // Read in the opening parentheses
        ss >> ch;

        // Parse buttons until you hit joltages
        int button = 0;
        while (ch != '{') {
            buttons.emplace_back();
            while (ch != ')') {
                ss >> n >> ch;
                buttons[button].push_back(n);
                // std::cout << n << " ";
            }
            button++;
            // std::cout << "\n";

            ss >> ch;
        }

        // Read in joltages
        int jlt_sum = 0;
        
        // std::cout << "Joltages: ";
        while (ch != '}') {
            ss >> n >> ch;
            joltages.push_back(n);
            jlt_sum += n;
            // std::cout << n << " ";
        }

        // std::cout << "\n";

        std::vector<bool> initA(target.size());
        int pressesA = singleLinePartA(target, initA, buttons, 0, target.size(), 0);
        partA += pressesA;
        std::cout << pressesA << " ";

        std::vector<int> initB(joltages.size());
        int pressesB = singleLinePartB(joltages, initB, buttons, jlt_sum, 0);
        partB += pressesB;
        std::cout << pressesB << "\n";
    }

    std::cout << "Part A solution: " << partA << "\n";
    std::cout << "Part B solution: " << partB << "\n";

    return 0;
}