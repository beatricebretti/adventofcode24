#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

// only part 1 for now
int main() {
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
    cout << sum << endl;
    return 0;
}