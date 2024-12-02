#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

int similarity(const vector<int>& left, const vector<int>& right);
int distance(const vector<int>& left, const vector<int>& right);

int main() {
    ifstream inputFile("input.txt");
    vector<int> left, right;
    int a, b;

    while (inputFile >> a >> b) {
        left.push_back(a); right.push_back(b);
    }
    cout << distance(left, right) << endl; cout << similarity(left, right) << endl;
    return 0;
}

int similarity(const vector<int>& left, const vector<int>& right) {
    unordered_map<int, int> counts;
    for (int num : right) { ++counts[num]; }

    int score = 0;
    for (int num : left) { score += num * counts[num]; }
    return score;
}

int distance(const vector<int>& left, const vector<int>& right) {
    vector<int> leftSorted = left; vector<int> rightSorted = right;
    sort(leftSorted.begin(), leftSorted.end()); sort(rightSorted.begin(), rightSorted.end());

    int total = 0;
    for (size_t i = 0; i < leftSorted.size(); ++i) {
        total += abs(leftSorted[i] - rightSorted[i]);
    }
    return total;
}