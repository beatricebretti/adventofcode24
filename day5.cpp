#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>

using namespace std;

unordered_map<int, unordered_set<int>> parse(const vector<string>& rules);
bool isValid(const vector<int>& update, const unordered_map<int, unordered_set<int>>& graph);
vector<int> correct(const vector<int>& update, const unordered_map<int, unordered_set<int>>& graph); // parte2 c:
int page(const vector<int>& update);

int main() {
    ifstream inputFile("input.txt");
    string line;
    vector<string> rules;
    vector<vector<int>> updates;

    while (getline(inputFile, line) && !line.empty()) { rules.push_back(line); }
    while (getline(inputFile, line)) {
        vector<int> update;
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) { update.push_back(stoi(token)); }
        updates.push_back(update);
    }
    inputFile.close();

    auto graph = parse(rules);
    int part1 = 0;
    int part2 = 0;
    vector<vector<int>> incorrect;
    for (const auto& update : updates) {
        if (isValid(update, graph)) { part1 += page(update); } 
        else { incorrect.push_back(update); }
    }

    for (const auto& update : incorrect) {
        auto corrected = correct(update, graph);
        part2 += page(corrected);
    }
    cout << part1 <<  endl; cout << part2 << endl;
    return 0;
}

int page(const vector<int>& update) { return update[update.size() / 2]; }

vector<int> correct(const vector<int>& update, const unordered_map<int, unordered_set<int>>& graph) {
    unordered_map<int, int> grado;
    unordered_map<int, unordered_set<int>> subGrafo;

    for (int page : update) { subGrafo[page]; }
    for (const auto& [x, ys] : graph) {
        if (subGrafo.count(x)) {
            for (int y : ys) {
                if (subGrafo.count(y)) {
                    subGrafo[x].insert(y);
                    grado[y]++;
                }
            }
        }
    }

    queue<int> q;
    for (int page : update) {
        if (grado[page] == 0) { q.push(page);}
    }
    vector<int> sorted;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        sorted.push_back(current);
        for (int neighbor : subGrafo[current]) {
            grado[neighbor]--;
            if (grado[neighbor] == 0) { q.push(neighbor); }
        }
    }
    return sorted;
}

bool isValid(const vector<int>& update, const unordered_map<int, unordered_set<int>>& graph) {
    unordered_map<int, int> pos;
    for (int i = 0; i < update.size(); ++i) { pos[update[i]] = i; }
    for (const auto& [x, ys] : graph) {
        if (pos.count(x)) {
            for (int y : ys) {
                if (pos.count(y) && pos[x] >= pos[y]) { return false; }
            }
        }
    }
    return true;
}

unordered_map<int, unordered_set<int>> parse(const vector<string>& rules) {
    unordered_map<int, unordered_set<int>> graph;
    for (const string& rule : rules) {
        int x, y;
        sscanf(rule.c_str(), "%d|%d", &x, &y);
        graph[x].insert(y);
    }
    return graph;
}