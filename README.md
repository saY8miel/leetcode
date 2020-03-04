# Solution: 1049. Last Stone Weight II

https://leetcode.com/problems/last-stone-weight-ii/

## Initial analysis

Let’s start with some observations. Let `n` denote the number of stones.

 1. We do not need to distinguish the case where `x == y`: if we allow `0` as a difference, the output
 (the final number) remains the same.
 1. The output is always the sum of some weights minus all the other weights: if the input is `[s_1, s_2, ..., s_n
 ]`, the output can always be formulated as <!--img src="https://render.githubusercontent.com/render/math?math=\sum_{i=1}^{n}{c_i s_i}"-->![sum ci si](img/math1.svg), where each coefficient `c_i` is either `+1` or `-1`.
 1. Every combination of coefficients corresponds to a sequence of smashing stones
  (keeping  non-negative `y-x` differences) such that the output is <!--img src="https://render.githubusercontent.com/render/math?math=\left|\sum_{i=1}^{n}{c_i  s_i}\right|"-->![|sum ci si|](img/math2.svg).

So this is actually the optimization version of the [Partition problem](https://en.wikipedia.org/wiki/Partition_problem), known to be NP-hard.

## Pseudo-polynomial Solution

As weights are between `0..100`, there is an efficient solution using the dynamic programming technique. Let us have a
2-dimensional array `D[j][i]` signaling `True` (`T`) if the value `i` can be the exact output from the first
`(j+1)` numbers, empty (`False`) otherwise. Filling `D[0][i]` is trivial: `D[0][s_1] := True` and the rest of this row is `False`.
For `j>0`, we can use the previous, `(j-1)`th row, and the new number `x` (the `(j+1)`th number, `s_(j+1)`):

`D[j][i]` := `True` exactly if `D[j-1][i+x]` or `D[j-1][abs(i-x)]`.

So for the input `[2,7,4,1,8,1]`, the array `D` looks as follows :

|j \ i |0|1|2|3|4|5|6|7|8|9|10|11|12|13|...|23|
|------|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|0, x=2| | |T| | | | | | | | | | | |...| |
|1, x=7| | | | | |T| | | |T| | | | |...| |
|2, x=4| |T| | | |T| | | |T| | | |T|...| |
|3, x=1|T| |T| |T| |T| |T| |T| |T| |...| |
|4, x=8|T| |T| |T| |T| |T| |T| |T| |...| |
|5, x=1| |***T***| |T| |T| |T| |T| |T| |T|...|T|

So we need to fill this 2D array `D` row by row, and the output is simply the smallest index `i` such that `D[n-1][i]` is `True`, which is `1` in this case.

## Source Code

```
const int NMAX = 30;
const int MMAX = 100;

using RowType = bitset<(NMAX+1) * MMAX + 1>;  // +1s guard buf overrun

int findFirstTrue(const RowType& row) {
    int i = 0;
    while (! row[i]) { i++; }
    return i;
}

int lastStoneWeightII(const vector<int>& stones) {
    auto d = array<RowType, NMAX>{};
    auto sum = 0;  // maximal index s.t. d[j] is True
    const auto n = (int)stones.size();
    for (auto j = 0; j != n; j++) {
        const auto x = stones[j];
        sum += x;
        if (j == 0) {
            d[j][x] = true;
            continue;
        }
        for (auto i = 0; i <= sum; i++) {
            d[j][i] = d[j - 1][i + x] || d[j - 1][abs(i - x)];
        }
    }
    return findFirstTrue(d[n - 1]);
}
``` 

## Complexity Analysis

Let `m` denote the maximal stone value, so `m <= 100`.

Space: `O(n^2*m)` for the current solution, as `D` has at most `n*m` columns and `n` rows. However, as we only use two rows instead of the whole matrix, the solution can be improved to use only `O(n*m)` space.

Runtime: `O(n^2*m)`.

