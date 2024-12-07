#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <tuple>

using namespace std;

struct Position {
    int x, y;
    char direction;
    void turnRight() {
        switch (direction) {
            case '^': direction = '>'; break;
            case '>': direction = 'v'; break;
            case 'v': direction = '<'; break;
            case '<': direction = '^'; break;
        }
    }
    void moveForward() {
        switch (direction) {
            case '^': x--; break;
            case '>': y++; break;
            case 'v': x++; break;
            case '<': y--; break;
        }
    }
};

bool isValid(int x, int y, const vector<string>& map) { return x >= 0 && x < map.size() && y >= 0 && y < map[0].size(); }
bool isObstacle(int x, int y, const vector<string>& map) { return isValid(x, y, map) && map[x][y] == '#'; }
bool isLoop(const vector<string>& map, int addX, int addY, Position guard) {
    vector<string> modifiedMap = map;
    modifiedMap[addX][addY] = '#'; 
    set<tuple<int, int, char>> seenStates;
    while (true) {
        if (seenStates.count({guard.x, guard.y, guard.direction})) { return true; }
        seenStates.insert({guard.x, guard.y, guard.direction});
        int nextX = guard.x, nextY = guard.y;
        switch (guard.direction) {
            case '^': nextX--; break;
            case '>': nextY++; break;
            case 'v': nextX++; break;
            case '<': nextY--; break;
        }
        if (isObstacle(nextX, nextY, modifiedMap)) { guard.turnRight(); } 
        else {
            guard.moveForward();
            if (!isValid(guard.x, guard.y, modifiedMap)) { return false; }
        }
    }
}

int main() {
    vector<string> map;
    string line;
    while (getline(cin, line)) { map.push_back(line); }
    Position guard;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '^' || map[i][j] == '>' || map[i][j] == 'v' || map[i][j] == '<') {
                guard = {i, j, map[i][j]};
                map[i][j] = '.';
                break;
            }
        }
    }
    set<pair<int, int>> visited;
    visited.insert({guard.x, guard.y});

    while (true) {
        int nextX = guard.x, nextY = guard.y;
        switch (guard.direction) {
            case '^': nextX--; break;
            case '>': nextY++; break;
            case 'v': nextX++; break;
            case '<': nextY--; break;
        }

        if (isObstacle(nextX, nextY, map)) { guard.turnRight(); } 
        else {
            guard.moveForward();
            if (!isValid(guard.x, guard.y, map)) { break; }
            visited.insert({guard.x, guard.y});
        }
    }

    int validPositions = 0;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '.' && (i != guard.x || j != guard.y)) {
                if (isLoop(map, i, j, guard)) {
                    validPositions++;
                }
            }
        }
    }
    cout << visited.size() << endl; cout << validPositions << endl;
    return 0;
}