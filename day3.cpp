#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int part1();
int part2();

int main() {
    cout << part1() << endl; cout << part2() << endl;
    return 0;
}

int part1() {
    ifstream inputFile("input.txt");

    string line; long long sum = 0;
    regex validRegex(R"(mul\((\d+),(\d+)\))");

    while (getline(inputFile, line)) {
        auto begin = sregex_iterator(line.begin(), line.end(), validRegex); auto end = sregex_iterator();

        for (auto it = begin; it != end; ++it) {
            smatch match = *it;
            int x = stoi(match[1].str());
            int y = stoi(match[2].str());
            sum += x * y;
        }
    }
    inputFile.close();
    return sum;
}

int part2() {
    ifstream inputFile("input.txt");
    
    string line; long long sum = 0;
    regex combinedRegex(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");
    bool enabled = true;

    while (getline(inputFile, line)) {
        auto begin = sregex_iterator(line.begin(), line.end(), combinedRegex); auto end = sregex_iterator();

        for (auto it = begin; it != end; ++it) {
            smatch match = *it;
            string matched = match.str();

            if (matched == "do()") { enabled = true; } 
            else if (matched == "don't()") { enabled = false; }
            else if (enabled && match[1].matched && match[2].matched) {
                int x = stoi(match[1].str());
                int y = stoi(match[2].str());
                sum += x * y;
            }
        }
    }
    inputFile.close();
    return sum;
}