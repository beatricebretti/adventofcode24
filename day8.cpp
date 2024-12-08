#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <tuple>
#include <algorithm>

using namespace std;

struct pos_t {
    int x, y;
    bool operator<(const pos_t& other) const { return tie(x, y) < tie(other.x, other.y); }
    pos_t operator+(const pos_t& other) const { return { x + other.x, y + other.y }; }
    pos_t operator-(const pos_t& other) const { return { x - other.x, y - other.y }; }
};

struct grid_t {
    map<char, vector<pos_t>> freq_pos; 
    int w = 0, h = 0;

    bool in_bounds(const pos_t& p) const { return p.x >= 0 && p.x < w && p.y >= 0 && p.y < h; }
};

grid_t load_map(const string& file);
size_t part1(const grid_t& grid);
size_t part2(const grid_t& grid);

int main() {
    auto grid = load_map("input.txt");
    cout << part1(grid) << endl; cout << part2(grid) << endl;
    return 0;
}

grid_t load_map(const string& file) {
    grid_t grid;
    ifstream fs(file);
    for (string line; getline(fs, line); grid.h++) {
        grid.w = max(grid.w, static_cast<int>(line.size()));
        for (int x = 0; x < line.size(); ++x) 
            if (line[x] != '.') grid.freq_pos[line[x]].push_back({ x, grid.h });
    }
    return grid;
}

size_t part1(const grid_t& grid) {
    set<pos_t> nodes;
    for (const auto& [f, pos] : grid.freq_pos)
        for (size_t i = 0; i < pos.size(); ++i)
            for (size_t j = i + 1; j < pos.size(); ++j) {
                pos_t delta = pos[i] - pos[j];
                if (grid.in_bounds(pos[i] + delta)) nodes.insert(pos[i] + delta);
                if (grid.in_bounds(pos[j] - delta)) nodes.insert(pos[j] - delta);
            }
    return nodes.size();
}

size_t part2(const grid_t& grid) {
    set<pos_t> nodes;
    for (const auto& [f, pos] : grid.freq_pos)
        for (size_t i = 0; i < pos.size(); ++i)
            for (size_t j = i + 1; j < pos.size(); ++j) {
                pos_t delta = pos[i] - pos[j];
                for (pos_t p = pos[i]; grid.in_bounds(p); p = p + delta) nodes.insert(p);
                for (pos_t p = pos[j]; grid.in_bounds(p); p = p - delta) nodes.insert(p);
            }
    return nodes.size();
}