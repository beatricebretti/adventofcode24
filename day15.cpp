#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <tuple>

using namespace std;

struct Pos { int x, y; };
bool operator==(const Pos& a, const Pos& b) { return tie(a.x, a.y) == tie(b.x, b.y); }
Pos operator+(const Pos& a, const Pos& b) { return {a.x + b.x, a.y + b.y}; }
struct Map {
    vector<char> grid, moves;
    Pos bot;
    int w = 0, h = 0;
    char& at(const Pos& p) { return grid[p.y * w + p.x]; }
    char at(const Pos& p) const { return grid[p.y * w + p.x]; }
};

Map load(const string& file);
map<char, Pos> dirs { {'>', {1, 0}}, {'v', {0, 1}}, {'<', {-1, 0}}, {'^', {0, -1}} };
int gps(const Map& m, char box);
bool tryMove(Map& m, const Pos& cur, const Pos& next, const Pos& dir, bool move = false);
void move(Map& m, const Pos& cur, const Pos& next, const Pos& dir);
Map expand(const Map& m);
int solve(const Map& in, bool expand_map);

int main() {
    auto m = load("input.txt");
    cout <<  solve(m, false) << endl; cout <<  solve(m, true) << endl;
}

Map load(const string& file) {
    Map m;
    ifstream fs(file);
    string line;
    bool reading_moves = false;

    while (getline(fs, line)) {
        if (line.empty()) { reading_moves = true; continue; }
        for (int x = 0; x < line.size(); ++x) {
            if (line[x] == '@') { m.bot = {x, m.h}; m.grid.push_back('.'); }
            else (reading_moves ? m.moves : m.grid).push_back(line[x]);
        }
        if (!reading_moves) { m.w = max(m.w, (int)line.size()); m.h++; }
    }
    return m;
}

int gps(const Map& m, char box) {
    int sum = 0;
    for (int y = 0; y < m.h; ++y) 
        for (int x = 0; x < m.w; ++x) 
            if (m.at({x, y}) == box) 
                sum += 100 * y + x;
    return sum;
}

bool tryMove(Map& m, const Pos& cur, const Pos& next, const Pos& dir, bool move = false) {
    if (m.at(next) == '[' || m.at(next) == ']' || m.at(next) == 'O') {
        if (m.at(next) != 'O' && (dir == dirs['^'] || dir == dirs['v'])) {
            if (m.at(next) == '[') 
                return tryMove(m, next, next + dir, dir, move) &&
                       tryMove(m, next + dirs['>'], (next + dirs['>']) + dir, dir, move);
            if (m.at(next) == ']') 
                return tryMove(m, next, next + dir, dir, move) &&
                       tryMove(m, next + dirs['<'], (next + dirs['<']) + dir, dir, move);
        } else 
            return tryMove(m, next, next + dir, dir, move);
    }
    if (m.at(next) == '#') return false;
    if (m.at(next) == '.' && move) swap(m.at(cur), m.at(next));
    return true;
}

void move(Map& m, const Pos& cur, const Pos& next, const Pos& dir) { tryMove(m, cur, next, dir, true);}

Map expand(const Map& m) {
    Map big;
    big.w = m.w * 2;
    big.h = m.h;
    big.grid.resize(big.w * big.h);
    big.moves = m.moves;

    for (int y = 0; y < m.h; ++y)
        for (int x = 0; x < m.w; ++x) {
            if (m.at({x, y}) == '#') {
                big.at({x * 2, y}) = '#';
                big.at({x * 2 + 1, y}) = '#';
            } else if (m.at({x, y}) == 'O') {
                big.at({x * 2, y}) = '[';
                big.at({x * 2 + 1, y}) = ']';
            } else if (m.at({x, y}) == '.') {
                big.at({x * 2, y}) = '.';
                big.at({x * 2 + 1, y}) = '.';
            }
            if (m.bot == Pos{x, y}) 
                big.bot = {x * 2, y};
        }
    return big;
}
int solve(const Map& in, bool expand_map) {
    Map m = expand_map ? expand(in) : in;
    Pos p = m.bot;

    for (auto mv : m.moves) {
        Pos next = p + dirs[mv];
        if (tryMove(m, p, next, dirs[mv])) {
            move(m, p, next, dirs[mv]);
            p = next;
        }
    }
    return gps(m, expand_map ? '[' : 'O');
}