# Q1. Minimum Coin Change

**Problem:** Given coin denominations `C = {c1, ..., cn}` (infinite supply) and a target `V`, find the minimum number of coins that sum to `V`, or `-1` if impossible.

## Approach (Dynamic Programming)

| Item | Definition |
|------|-----------|
| State | `dp[v]` = minimum coins needed to make amount `v` |
| Base case | `dp[0] = 0` |
| Recurrence | `dp[v] = 1 + min(dp[v - c])` over all coins `c <= v` with `dp[v - c]` reachable |
| Answer | `dp[V]`, or `-1` if `dp[V] = INF` |

**Optimal substructure:** if the last coin used is `c`, the remaining `v - c` must itself be made with the fewest coins.

## Input representation
* `n` and `V` as integers, coin array `C[0..n-1]`
* table `dp[0..V]` initialised to `INF`

## Pseudocode

```text
MIN-COIN-CHANGE(C[1..n], V)
1   let dp[0..V] be a new array
2   dp[0] = 0
3   for v = 1 to V
4       dp[v] = INF
5       for i = 1 to n
6           if C[i] <= v and dp[v - C[i]] != INF
7               dp[v] = min(dp[v], dp[v - C[i]] + 1)
8   if dp[V] == INF return -1
9   return dp[V]
```

## Example
`C = {1, 5, 6}`, `V = 11`

| v | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 |
|---|---|---|---|---|---|---|---|---|---|---|----|----|
| dp[v] | 0 | 1 | 2 | 3 | 4 | 1 | 1 | 2 | 3 | 4 | 2 | **2** |

Answer = 2 (5 + 6). A greedy choice (6 + 1x5) would give 6 coins, so DP is needed.

## Complexity
* Outer loop runs `V` times, inner loop `n` times, each step O(1): `T(n,V) = sum_{v=1..V} n = nV` => **Time O(nV)**
* One array of size `V + 1` => **Space O(V)**
* This is pseudo-polynomial: polynomial in the value `V`, exponential in the number of bits of `V`.
