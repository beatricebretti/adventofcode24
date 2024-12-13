#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct Vec2 {
    int x, y;
};
struct GameParameters {
    Vec2 a, b, target;
};

Vec2 vec2(const string& line, int offset);
vector<GameParameters> parseInput(const string& filename);

int main() {
    auto games = parseInput("input.txt");
    int part1 = 0;
    uint64_t part2 = 0;

    for (const auto& game : games) {
        double det = game.a.x * game.b.y - game.a.y * game.b.x;
        if (det == 0) continue;
        auto solve = [&](double c1, double c2) -> pair<double, double> {
            double x = (-c2 * game.b.x + c1 * game.b.y) / det;
            double y = (c2 - x * game.a.y) / game.b.y;
            return {x, y};
        };

        auto [x1, y1] = solve(game.target.x, game.target.y);
        if (floor(x1) == x1 && floor(y1) == y1 && x1 >= 0 && y1 >= 0)
            part1 += x1 * 3 + y1;
        auto [x2, y2] = solve(game.target.x + 1e13, game.target.y + 1e13);
        if (floor(x2) == x2 && floor(y2) == y2 && x2 >= 0 && y2 >= 0)
            part2 += x2 * 3 + y2;
    }
    cout << part1 << "\n"; cout << part2 << "\n";
    return 0;
}

Vec2 vec2(const string& line, int offset) {
    size_t comma_pos = line.find(',');
    return {stoi(line.substr(offset, comma_pos - offset)), stoi(line.substr(comma_pos + 4))};
}

vector<GameParameters> parseInput(const string& filename) {
    ifstream file(filename);
    vector<GameParameters> games;
    string line;
    while (getline(file, line)) {
        Vec2 a = vec2(line, 12);
        getline(file, line);
        Vec2 b = vec2(line, 12);
        getline(file, line);

        size_t equal_pos = line.find('='), comma_pos = line.find(',');
        Vec2 target = {stoi(line.substr(equal_pos + 1, comma_pos - equal_pos - 1)), stoi(line.substr(comma_pos + 4))};
        games.push_back({a, b, target});
        getline(file, line); 
    }
    return games;
}