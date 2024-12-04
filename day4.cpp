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
bool hasX(const vector<string>& grid, int row, int col);
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
bool hasX(const vector<string>& grid, int row, int col) {
    int rows = grid.size(); int cols = grid[0].size();

    if (row + 2 >= rows || col - 1 < 0 || col + 1 >= cols) { return false; }
    bool firstRowValid = (grid[row][col - 1] == 'M' && grid[row][col + 1] == 'S') ||
                         (grid[row][col - 1] == 'S' && grid[row][col + 1] == 'M');
    bool thirdRowValid = (grid[row + 2][col - 1] == 'M' && grid[row + 2][col + 1] == 'S') ||
                         (grid[row + 2][col - 1] == 'S' && grid[row + 2][col + 1] == 'M');
    bool middleRowValid = (grid[row + 1][col] == 'A');
    return firstRowValid && middleRowValid && thirdRowValid;
}
int countX(const vector<string>& grid) {
    int rows = grid.size(); int cols = grid[0].size();
    
    int count = 0;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) { if (hasX(grid, row, col)) { ++count; } }
    }
    return count;
}