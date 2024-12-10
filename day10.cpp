#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <queue>

using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

bool is_valid(int x, int y, int rows, int cols) { return x >= 0 && x < rows && y >= 0 && y < cols;}

int bfs(const vector<vector<int>>& map, int start_x, int start_y) {
    int rows = map.size(); int cols = map[0].size();
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    q.push({start_x, start_y});
    visited[start_x][start_y] = true;

    int score = 0;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (map[x][y] == 9) {
            score++;
            continue;
        }
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (is_valid(nx, ny, rows, cols) && !visited[nx][ny] && map[nx][ny] == map[x][y] + 1) {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }

    return score;
}

void rating_dfs(const vector<vector<int>>& map, int x, int y, set<string>& trails, string current_path) {
    int rows = map.size();
    int cols = map[0].size();
    current_path += to_string(x) + "," + to_string(y) + ";";
    if (map[x][y] == 9) {
        trails.insert(current_path);
        return;
    }

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (is_valid(nx, ny, rows, cols) && map[nx][ny] == map[x][y] + 1) { rating_dfs(map, nx, ny, trails, current_path);}
    }
}

int dfs(const vector<vector<int>>& map, int start_x, int start_y) {
    set<string> trails;
    rating_dfs(map, start_x, start_y, trails, "");
    return trails.size();
}

int main() {
    ifstream input("input.txt");
    vector<vector<int>> map;
    string line;

    while (getline(input, line)) {
        vector<int> row;
        for (char c : line) { row.push_back(c - '0');}
        map.push_back(row);
    }

    input.close();

    int total_score = 0;
    int total_rating = 0;

    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] == 0) {
                total_score += bfs(map, i, j);
                total_rating += dfs(map, i, j);
            }
        }
    }
    cout << total_score << endl; cout <<  total_rating << endl;
    return 0;
}