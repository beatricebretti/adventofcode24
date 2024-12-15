#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;
struct Robot { int x, y, vx, vy; };

vector<Robot> parseInput(const string& filename) {
    vector<Robot> robots;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        Robot robot;
        istringstream(line) >> ws >> ws >> robot.x >> ws >> robot.y >> ws >> ws >> robot.vx >> ws >> robot.vy;
        robots.push_back(robot);
    }
    return robots;
}

void simulateRobots(vector<Robot>& robots, int time = 100, int width = 101, int height = 103) {
    for (int t = 0; t < time; ++t)
        for (auto& robot : robots)
            robot.x = (robot.x + robot.vx + width) % width, robot.y = (robot.y + robot.vy + height) % height;
}

int calculateSafetyFactor(const vector<Robot>& robots, int width = 101, int height = 103) {
    int q1 = 0, q2 = 0, q3 = 0, q4 = 0, midX = width / 2, midY = height / 2;
    for (const auto& robot : robots) {
        if (robot.x == midX || robot.y == midY) continue;
        (robot.x < midX && robot.y < midY ? ++q1 : robot.x >= midX && robot.y < midY ? ++q2 : robot.x < midX && robot.y >= midY ? ++q3 : ++q4);
    }
    return q1 * q2 * q3 * q4;
}

int main() {
    auto robots = parseInput("input.txt");
    simulateRobots(robots, 100);
    cout << calculateSafetyFactor(robots) << endl;
    return 0;
}