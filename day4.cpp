#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//feliz navidad hihihiihiihi
const string XMAS = "XMAS";
const int XMAS_LEN = XMAS.length();
const vector<pair<int, int>> DIR = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

bool hasXMAS(const vector<string>& grid, int row, int col, pair<int, int> direction);
int countXMAS(const vector<string>& grid);
bool hasX(const string& s);
int countX(const vector<string>& grid);

int main() {
    ifstream inputFile("input.txt");
    vector<string> grid;
    string line;

    while (getline(inputFile, line)) {
        grid.push_back(line);
    }
    inputFile.close();
    cout << countXMAS(grid) << endl; cout << countX(grid) << endl;
    return 0;
}

// ------------------- part1 ---------------------------------
bool hasXMAS(const vector<string>& grid, int row, int col, pair<int, int> direction) {
    int rows = grid.size(); int cols = grid[0].size();

    for (int i = 0; i < XMAS_LEN; ++i) {
        int newRow = row + i * direction.first; int newCol = col + i * direction.second;
        if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols || grid[newRow][newCol] != XMAS[i]) {
            return false;
        }
    }
    return true;
}
int countXMAS(const vector<string>& grid) {
    int rows = grid.size(); int cols = grid[0].size();

    int count = 0;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            for (const auto& dir : DIR) { if (hasXMAS(grid, row, col, dir)) { ++count; } }
        }
    }
    return count;
}

// -------------------- part2 -------------------------------------
bool hasX(const string& s) { return s == "MAS" || s == "SAM";}
int countX(const vector<string>& grid) {
    int rows = grid.size(); int cols = grid[0].size();

    int count = 0;
    for (int r = 0; r <= rows - 3; ++r) {
        for (int c = 0; c <= cols - 3; ++c) {
            string diag1 = {grid[r][c], grid[r+1][c+1], grid[r+2][c+2]};
            string diag2 = {grid[r][c+2], grid[r+1][c+1], grid[r+2][c]};
            if (hasX(diag1) && hasX(diag2)) { ++count; }
        }
    }
    return count;
}