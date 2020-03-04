#include "include/utils.h"

const int NMAX = 30;
const int MMAX = 100;

class Solution {
    using RowType = bitset<(NMAX+1) * MMAX + 1>;  // +1s guard buf overrun
    int findFirstTrue(const RowType& row) {
        int i = 0;
        while (! row[i]) { i++; }
        return i;
    }
    void print(const RowType& row, int sum) {
        cout << "  ";
        for (auto i = 0; i <= sum; i++) { cout << (row[i] ? 'T' : ' ') << ' '; }
        cout << "|\n";
    }
public:
    int lastStoneWeightII(const vector<int>& stones) {
        //cout << "  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9\n";
        auto d = array<RowType, NMAX>{};
        auto sum = 0;  // maximal index s.t. d[j] is True
        const auto n = (int)stones.size();
        for (auto j = 0; j != n; j++) {
            const auto x = stones[j];
            sum += x;
            if (j==0) {
                d[j][x] = true;
                //print(d[0], sum);
                continue;
            }
            auto& curr = d[j];
            const auto& prev = d[j-1];
            for (auto i = 0; i <= sum; i++) {
                curr[i] = prev[i+x] || prev[abs(i-x)];
            }
            //print(d[j], sum);
        }
        return findFirstTrue(d[n - 1]);
    }
};

class GenerateAndTestSolution {
// let's store 30 bits in an unsigned int
static_assert((long long)UINT_MAX > (1ll<<NMAX));
    int lowerBound(const vector<int>& stones) {
        // two lower bounds: parity and max-(sum-max)
        const auto sum = accumulate(stones.begin(), stones.end(), 0);
        const auto parity = sum % 2;
        const auto max = *max_element(stones.begin(), stones.end());
        const auto lb2 = std::max(0, max-(sum-max));
        // write(stones);
        // cout << "lbs: " << parity << " " << lb2 << "\n";
        return std::max(parity, lb2);
    }
    int computeSum(const bitset<NMAX>& bits, const vector<int>& stones) {
        auto b = 0;
        auto sum = 0;
        for (auto s : stones) {
            sum += (bits[b++] ? +1 : -1) * s;
        }
        return abs(sum);
    }
public:
    int lastStoneWeightII(vector<int>& stones) {
        const unsigned combinations = 1 << stones.size();
        auto best = INT_MAX;
        const auto lb = lowerBound(stones);
        for (unsigned comb = 0; comb != combinations; comb++) {
            const auto bits = bitset<NMAX>{comb};
            //cout << bits << "\n";
            const auto sum = computeSum(bits, stones);
            //cout << sum << "\n";
            best = min(best, sum);
            if (best == lb) {
                //cout << "pruning for " << bits << "\n";
                return best;
            }
        }
        return best;
    }
};

//struct Solution : DinProgSolution {};
//struct Solution : BruteForceSolution {};
//struct Solution : GenerateAndTestSolution {};

int main() {
    auto t2 = vector<int>{2,1,6,4,5};
    auto t1 = vector<int>{2,7,4,1,8,1};
    write(t1);
    cout << Solution().lastStoneWeightII(t1) << endl;
    cout << GenerateAndTestSolution().lastStoneWeightII(t1) << endl;
}
