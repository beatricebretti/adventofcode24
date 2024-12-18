#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <functional>
#include <cmath>

using namespace std;

class CPU {
    vector<uint64_t> regs, prog, out;
    uint64_t curInst = 0;
    uint64_t resolveOp(uint64_t op) { return op < 4 ? op : regs[op - 4]; }
    vector<function<void(uint64_t)>> instSet = {
        [this](uint64_t op) { regs[0] /= pow(2, resolveOp(op)); },
        [this](uint64_t op) { regs[1] ^= op; },
        [this](uint64_t op) { regs[1] = resolveOp(op) % 8; },
        [this](uint64_t op) { if (regs[0] != 0) curInst = 2 * op; },
        [this](uint64_t) { regs[1] ^= regs[2]; },
        [this](uint64_t op) { out.push_back(resolveOp(op) % 8); },
        [this](uint64_t op) { regs[1] = regs[0] / pow(2, resolveOp(op)); },
        [this](uint64_t op) { regs[2] = regs[0] / pow(2, resolveOp(op)); }
    };
    void step() {
        instSet[prog[curInst]](prog[curInst + 1]);
        curInst += 2;
    }
    void run() { while (curInst < prog.size() - 1) step(); }
public:
    CPU(vector<uint64_t> r, vector<uint64_t> p) : regs(move(r)), prog(move(p)) {}
    string getOut() {
        run();
        string res;
        for (size_t i = 0; i < out.size(); ++i)
            res += (i > 0 ? "," : "") + to_string(out[i]);
        return res;
    }
    bool matchesOut(size_t idx) {
        run();
        return equal(out.begin(), out.end(), prog.begin() + idx);
    }
};

vector<uint64_t> extractNums(string ln);
pair<vector<uint64_t>, vector<uint64_t>> parseFile(string fName);
uint64_t findRegs(vector<uint64_t> prog, size_t idx, uint64_t curA);
void solve();

int main() {
    solve();
    return 0;
}

vector<uint64_t> extractNums(string ln) {
    regex numRegex(R"(\d+)");
    return {sregex_token_iterator(ln.begin(), ln.end(), numRegex), {}};
}

pair<vector<uint64_t>, vector<uint64_t>> parseFile(string fName) {
    ifstream file(fName);
    string ln;
    vector<uint64_t> regs, prog;
    while (getline(file, ln) && !ln.empty())
        regs.push_back(stoull(extractNums(ln)[0]));
    getline(file, ln);
    prog = extractNums(ln);
    return {regs, prog};
}

uint64_t findRegs(vector<uint64_t> prog, size_t idx, uint64_t curA) {
    for (uint64_t i = 0; i < 8; ++i) {
        uint64_t nextA = curA * 8 + i;
        if (CPU({nextA, 0, 0}, prog).matchesOut(idx)) return idx == 0 ? nextA : findRegs(prog, idx - 1, nextA); }
    return UINT64_MAX;
}

void solve() {
    auto [regs, prog] = parseFile("input.txt");
    cout << CPU(regs, prog).getOut() << endl; cout << findRegs(prog, prog.size() - 1, 0) << endl;
}