#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

long long part1(const vector<int> &nums);
long long part2(const vector<int> &nums);

int main() {
    fstream file("input.txt");
    vector<int> nums;
    string line;
    getline(file, line);
    for (char c : line) nums.push_back(c - '0');
    file.close();

    cout << part1(nums) << endl; cout << part2(nums) << endl;
    return 0;
}

long long part1(const vector<int> &nums) {
    vector<int> disk;
    for (int i = 0; i < nums.size(); i++) 
        disk.insert(disk.end(), nums[i], (i % 2 == 0) ? i / 2 : -1);
    int left = 0, right = disk.size() - 1;
    while (left < right) {
        if (disk[left] == -1 && disk[right] != -1) { 
            swap(disk[left], disk[right]); 
            continue; 
        }
        if (disk[left] != -1) left++;
        if (disk[right] == -1) right--;
    }

    long long checksum = 0;
    for (int i = 0; i < disk.size() && disk[i] != -1; i++) 
        checksum += i * disk[i];
    return checksum;
}

long long part2(const vector<int> &nums) {
    unordered_map<int, int> size, pos;
    int idx = 0, offset = 0;
    for (int i = 0; i < nums.size(); i++) {
        int id = (i % 2 == 0) ? i / 2 : -(i / 2 + 1);
        if (i % 2 == 0) idx = id;
        size[id] = nums[i];
        pos[id] = offset;
        offset += nums[i];
    }

    while (idx > 0) {
        for (int i = 1; i <= idx; i++) {
            if (size[-i] < size[idx]) continue;
            size[-i] -= size[idx];
            pos[idx] = pos[-i];
            pos[-i] += size[idx];
            break;
        }
        idx--;
    }
    long long checksum = 0;
    for (const auto &[id, p] : pos) {
        if (id < 0) continue;
        for (int i = 0; i < size[id]; i++) checksum += id * (p + i);
    }
    return checksum;
}