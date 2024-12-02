#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

bool isSafe1(const vector<int>& levels);
bool isSafe2(const vector<int>& levels);

int main() {
    ifstream inputFile("input.txt");

    string line;
    int count = 0; int count2 = 0;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        vector<int> levels;
        int level;

        while (iss >> level) { levels.push_back(level); }
        if (isSafe1(levels)) { ++count; }
        if (isSafe2(levels)) { ++count2; }
    }
    inputFile.close();
    cout << count << endl; cout << count2 << endl;
    return 0;
}

// Part1 of the day c:
bool isSafe1(const vector<int>& levels) {
    if (levels.size() < 2) { return false; }

    bool incr = true;
    bool decr = true;

    for (size_t i = 1; i < levels.size(); ++i) {
        int diff = levels[i] - levels[i - 1];
        if (abs(diff) < 1 || abs(diff) > 3) { return false; }
        if (diff > 0) { decr = false; }
        else if (diff < 0) { incr = false; }
    }
    return incr || decr;
}

// Part2 of the day C:
bool isSafe2(const vector<int>& levels) {
    for (size_t i = 0; i < levels.size(); ++i) {
        vector<int> modif;
        for (size_t j = 0; j < levels.size(); ++j) {
            if (j != i) { modif.push_back(levels[j]); }
        }
        if (isSafe1(modif)) { return true; }
    }
    return false;
}