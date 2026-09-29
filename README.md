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

# Q2. Coin Change: Total Number of Ways

**Problem:** Given distinct positive coins `C = {c1, ..., cn}` (infinite supply) and a target `V`, count the distinct **combinations** that sum to `V`. Order does not matter (`1+2` and `2+1` are the same).

## Approach (Dynamic Programming)

| Item | Definition |
|------|-----------|
| State | `dp[v]` = number of combinations using the coins processed so far that sum to `v` |
| Base case | `dp[0] = 1` (the empty combination) |
| Recurrence | for each coin `c` (outer loop), for `v = c..V`: `dp[v] += dp[v - c]` |
| Answer | `dp[V]` |

**Why the coin loop is outside:** each coin is introduced once, so a combination is built in one fixed coin order. Swapping the loops would count permutations (ordered ways) instead.

## Pseudocode

```text
COIN-WAYS(C[1..n], V)
1   let dp[0..V] be an array of zeros
2   dp[0] = 1
3   for i = 1 to n                  // coins outer => order ignored
4       for v = C[i] to V
5           dp[v] = dp[v] + dp[v - C[i]]
6   return dp[V]
```

## Example
`C = {1, 2, 5}`, `V = 5`

| after coin | dp[0..5] |
|-----------|----------|
| none | 1 0 0 0 0 0 |
| 1 | 1 1 1 1 1 1 |
| 2 | 1 1 2 2 3 3 |
| 5 | 1 1 2 2 3 **4** |

Answer = 4: `{5}`, `{2,2,1}`, `{2,1,1,1}`, `{1,1,1,1,1}`.

## Complexity
* Coin `i` performs `V - C[i] + 1 <= V` updates: total <= `nV` => **Time O(nV)**
* One array of size `V + 1` => **Space O(V)**
* The count can grow large, so use a 64-bit unsigned type.

# Q3. Longest Common Subsequence (LCS)

**Problem:** Given `X = <x1..xm>` and `Y = <y1..yn>`, compute the length of their LCS and reconstruct one LCS string.

## Approach (Dynamic Programming)

| Item | Definition |
|------|-----------|
| State | `L[i][j]` = LCS length of prefixes `X[1..i]` and `Y[1..j]` |
| Base case | `L[i][0] = L[0][j] = 0` |
| Recurrence | `L[i][j] = L[i-1][j-1] + 1` if `X[i] == Y[j]`, else `max(L[i-1][j], L[i][j-1])` |
| Answer | `L[m][n]` |

## Input representation
Two character arrays `X[1..m]`, `Y[1..n]`; table `L[0..m][0..n]`.

## Pseudocode

```text
LCS(X[1..m], Y[1..n])
1   for i = 0 to m: L[i][0] = 0
2   for j = 0 to n: L[0][j] = 0
3   for i = 1 to m
4       for j = 1 to n
5           if X[i] == Y[j]
6               L[i][j] = L[i-1][j-1] + 1
7           else L[i][j] = max(L[i-1][j], L[i][j-1])
8   return L[m][n]

RECONSTRUCT(L, X, Y)                // walk back from (m, n)
1   i = m, j = n, k = L[m][n]
2   while i > 0 and j > 0
3       if X[i] == Y[j]
4           S[k] = X[i]; k = k - 1; i = i - 1; j = j - 1
5       else if L[i-1][j] >= L[i][j-1]  i = i - 1
6       else j = j - 1
7   return S
```

## Example
`X = AGGTAB`, `Y = GXTXAYB` => length **4**, LCS = **GTAB**.

## Complexity
* Table has `(m+1)(n+1)` cells, each filled in O(1) => **Time O(mn)**
* Traceback moves one step up/left per iteration: at most `m + n` steps => O(m + n)
* Full table needed for reconstruction => **Space O(mn)** (O(min(m,n)) if only the length is required)

# Q4. Longest Increasing Subsequence (LIS)

**Problem:** Given `A[0..n-1]`, find the length of the longest **strictly increasing** subsequence.

## Approach 1: Dynamic Programming, O(n^2)

| Item | Definition |
|------|-----------|
| State | `dp[i]` = length of the LIS **ending at** index `i` |
| Base case | `dp[i] = 1` (the element alone) |
| Recurrence | `dp[i] = 1 + max(dp[j])` over `j < i` with `A[j] < A[i]` |
| Answer | `max(dp[i])` over all `i` |

```text
LIS(A[0..n-1])
1   best = 0
2   for i = 0 to n-1
3       dp[i] = 1
4       for j = 0 to i-1
5           if A[j] < A[i] and dp[j] + 1 > dp[i]
6               dp[i] = dp[j] + 1
7       best = max(best, dp[i])
8   return best
```

## Approach 2 (optional): Binary search, O(n log n)
Keep `tails[k]` = smallest possible last element of an increasing subsequence of length `k+1`.

```text
LIS-FAST(A[0..n-1])
1   len = 0
2   for each x in A
3       pos = lower_bound(tails[0..len-1], x)   // first index with tails[pos] >= x
4       tails[pos] = x
5       if pos == len: len = len + 1
6   return len
```

## Example
`A = [10, 22, 9, 33, 21, 50, 41, 60]`

| i | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---|---|---|---|---|---|---|---|---|
| A[i] | 10 | 22 | 9 | 33 | 21 | 50 | 41 | 60 |
| dp[i] | 1 | 2 | 1 | 3 | 2 | 4 | 4 | **5** |

LIS length = 5, e.g. `10, 22, 33, 50, 60`.

## Complexity
* Approach 1: inner loop runs `i` times => `sum_{i=0..n-1} i = n(n-1)/2` => **Time O(n^2)**, **Space O(n)**
* Approach 2: `n` binary searches of O(log n) => **Time O(n log n)**, **Space O(n)**

# Q5. Maximum Sum Increasing Subsequence (MSIS)

**Problem:** Given `n` positive integers `A[0..n-1]`, find the maximum possible sum of a **strictly increasing** subsequence.

## Approach (Dynamic Programming)
This is the LIS recurrence with *values summed* instead of *lengths counted*.

| Item | Definition |
|------|-----------|
| State | `ms[i]` = maximum sum of an increasing subsequence **ending at** index `i` |
| Base case | `ms[i] = A[i]` |
| Recurrence | `ms[i] = A[i] + max(ms[j])` over `j < i` with `A[j] < A[i]` |
| Answer | `max(ms[i])` over all `i` |

## Pseudocode

```text
MSIS(A[0..n-1])
1   best = 0
2   for i = 0 to n-1
3       ms[i] = A[i]
4       for j = 0 to i-1
5           if A[j] < A[i] and ms[j] + A[i] > ms[i]
6               ms[i] = ms[j] + A[i]
7       best = max(best, ms[i])
8   return best
```

## Example
`A = [1, 101, 2, 3, 100, 4, 5]`

| i | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|---|---|---|---|---|---|---|---|
| A[i] | 1 | 101 | 2 | 3 | 100 | 4 | 5 |
| ms[i] | 1 | 102 | 3 | 6 | **106** | 10 | 15 |

Answer = 106 (`1 + 2 + 3 + 100`).

## Complexity
* Nested loops: `sum_{i=0..n-1} i = n(n-1)/2` => **Time O(n^2)**
* One array of size `n` => **Space O(n)**
* Use a 64-bit sum to avoid overflow.

# Q6. Edit Distance with Traceback

**Problem:** Given strings `A` (length `m`) and `B` (length `n`), find the minimum number of insertions, deletions and substitutions to turn `A` into `B`, and print the operations (traceback).

## Approach (Dynamic Programming)

| Item | Definition |
|------|-----------|
| State | `D[i][j]` = edit distance between `A[1..i]` and `B[1..j]` |
| Base cases | `D[i][0] = i` (delete all), `D[0][j] = j` (insert all) |
| Recurrence | `D[i][j] = D[i-1][j-1]` if `A[i] == B[j]`, else `1 + min(D[i-1][j-1], D[i-1][j], D[i][j-1])` |
| Answer | `D[m][n]` |

The three options in the `min` are **substitute**, **delete** `A[i]`, and **insert** `B[j]`.

## Pseudocode

```text
EDIT-DISTANCE(A[1..m], B[1..n])
1   for i = 0 to m: D[i][0] = i
2   for j = 0 to n: D[0][j] = j
3   for i = 1 to m
4       for j = 1 to n
5           if A[i] == B[j]
6               D[i][j] = D[i-1][j-1]
7           else D[i][j] = 1 + min(D[i-1][j-1], D[i-1][j], D[i][j-1])
8   return D[m][n]

TRACEBACK(i, j)                      // call TRACEBACK(m, n); prints in forward order
1   if i == 0 and j == 0 return
2   if i>0, j>0, A[i]==B[j], D[i][j]==D[i-1][j-1]
3       TRACEBACK(i-1, j-1);  print "Match A[i]"
4   else if i>0, j>0, D[i][j] == D[i-1][j-1] + 1
5       TRACEBACK(i-1, j-1);  print "Replace A[i] -> B[j]"
6   else if i>0, D[i][j] == D[i-1][j] + 1
7       TRACEBACK(i-1, j);    print "Delete A[i]"
8   else
9       TRACEBACK(i, j-1);    print "Insert B[j]"
```

## Example
`A = kitten`, `B = sitting` => distance **3**

```text
Replace k -> s
Match   i
Match   t
Match   t
Replace e -> i
Match   n
Insert  g
```

## Complexity
* `(m+1)(n+1)` cells, each O(1) => **Time O(mn)**
* Traceback takes at most `m + n` steps => O(m + n)
* Full table kept for traceback => **Space O(mn)**

# Q7. Rod Cutting with Reconstruction

**Problem:** A rod of length `n` and prices `P[1..n]` (`P[i]` = price of a piece of length `i`). Find (i) the maximum revenue and (ii) the lengths of the pieces in an optimal cut.

## Approach (Dynamic Programming)

| Item | Definition |
|------|-----------|
| State | `r[j]` = maximum revenue for a rod of length `j` |
| Base case | `r[0] = 0` |
| Recurrence | `r[j] = max(P[i] + r[j - i])` for `i = 1..j` (first piece has length `i`) |
| Reconstruction | `cut[j]` = the `i` that achieved the maximum |
| Answer | `r[n]` |

## Pseudocode

```text
ROD-CUTTING(P[1..n], n)
1   r[0] = 0
2   for j = 1 to n
3       r[j] = -INF
4       for i = 1 to j
5           if P[i] + r[j - i] > r[j]
6               r[j] = P[i] + r[j - i]
7               cut[j] = i
8   return r[n], cut

PRINT-CUTS(cut, n)
1   while n > 0
2       print cut[n]
3       n = n - cut[n]
```

## Example
`P = [1, 5, 8, 9, 10, 17, 17, 20]`, `n = 8`

| j | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
|---|---|---|---|---|---|---|---|---|
| r[j] | 1 | 5 | 8 | 10 | 13 | 17 | 18 | **22** |
| cut[j] | 1 | 2 | 3 | 2 | 2 | 6 | 1 | 2 |

Max revenue = 22, pieces = `2 + 6`.

## Complexity
* For each `j` the inner loop runs `j` times: `sum_{j=1..n} j = n(n+1)/2` => **Time O(n^2)**
* Arrays `r` and `cut` of size `n + 1` => **Space O(n)**
* Reconstruction takes O(n)

# Q8. Optimal Binary Search Tree (OBST)

**Problem:** Sorted keys `k1 < ... < kn` with search probabilities `p1..pn`, and dummy keys `d0..dn` (unsuccessful searches) with probabilities `q0..qn`, where `sum(p) + sum(q) = 1`. Find the BST with the minimum expected search cost.

## Approach (Dynamic Programming)

Let a subtree contain keys `ki..kj` and dummies `d(i-1)..dj`.

| Item | Definition |
|------|-----------|
| `w[i][j]` | total probability of the subtree: `sum(p_i..p_j) + sum(q_(i-1)..q_j)` |
| `e[i][j]` | expected search cost of an optimal BST on `ki..kj` |
| Base case | `e[i][i-1] = w[i][i-1] = q_(i-1)` (empty subtree, just a dummy key) |
| Recurrence | `e[i][j] = min over r in [i..j] of ( e[i][r-1] + e[r+1][j] + w[i][j] )` |
| Reconstruction | `root[i][j]` = the `r` achieving the minimum |
| Answer | `e[1][n]` |

**Why `+ w[i][j]`:** placing `kr` as root pushes every node of both subtrees one level deeper, adding their total probability `w[i][j]` to the cost.

## Pseudocode

```text
OPTIMAL-BST(p[1..n], q[0..n], n)
1   for i = 1 to n + 1
2       e[i][i-1] = q[i-1]
3       w[i][i-1] = q[i-1]
4   for len = 1 to n
5       for i = 1 to n - len + 1
6           j = i + len - 1
7           e[i][j] = INF
8           w[i][j] = w[i][j-1] + p[j] + q[j]
9           for r = i to j
10              t = e[i][r-1] + e[r+1][j] + w[i][j]
11              if t < e[i][j]
12                  e[i][j] = t;  root[i][j] = r
13  return e[1][n], root
```

## Example
`p = [0.15, 0.10, 0.05, 0.10, 0.20]`, `q = [0.05, 0.10, 0.05, 0.05, 0.05, 0.10]`

Minimum expected cost = **2.75**, root = `k2`; `k1` is its left child and `k5` its right child, with `k4` and `k3` below `k5`.

## Complexity
* Number of subproblems `(i, j)`: O(n^2); each tries up to `len` roots.
* Total work: `sum_{len=1..n} (n - len + 1) * len = n(n+1)(n+2)/6` => **Time O(n^3)** (Knuth's optimisation reduces this to O(n^2))
* Tables `e`, `w`, `root` of size about `n x n` => **Space O(n^2)**

# Q9. Collatz Conjecture (Open Problem)

**Definition:** For a positive integer `n`:

```text
T(n) = n / 2        if n is even
T(n) = 3n + 1       if n is odd
```

**Conjecture (unproven):** repeated application of `T` reaches `1` for every `n >= 1`.

**Task:** analyse the trajectory of a user-given `n >= 1`, and analyse all values in an interval `[a, b]`.

## Modules

| Function | Responsibility |
|----------|----------------|
| `next(n)` | returns `T(n)`, or `0` if `3n+1` would overflow 64 bits |
| `trajectory(n)` | prints the sequence, step count and peak value |
| `analyseInterval(a, b)` | finds the start value with the longest trajectory in `[a, b]` and the average step count |

## Overflow handling
For odd `n`, `3n + 1` fits in `unsigned long long` only if `n <= (ULLONG_MAX - 1) / 3`. The test is done **before** multiplying.

## Pseudocode

```text
NEXT(n)
1   if n is even return n / 2
2   if n > (MAX - 1) / 3 return 0          // overflow
3   return 3n + 1

TRAJECTORY(n)
1   steps = 0, peak = n
2   print n
3   while n != 1
4       nx = NEXT(n)
5       if nx == 0: report overflow; return
6       n = nx; steps++; peak = max(peak, n); print n
7   report steps, peak

ANALYSE-INTERVAL(a, b)                      // memoised
1   allocate cache[0..b] = 0                // cache[1] = 0
2   for i = 2 to b
3       cur = i, s = 0
4       while cur >= i                       // stop once below i: already cached
5           cur = NEXT(cur); s++             // (check overflow)
6       cache[i] = s + cache[cur]
7       if i >= a: update best (longest) and running total
8   report best start value, its steps, and average = total / (b - a + 1)
```

**Why the memoisation is valid:** values are processed in increasing order, so once a walk from `i` drops below `i`, the remaining steps are already stored in `cache`.

## Example
`n = 27` => **111 steps**, peak **9232**.
Interval `[1, 100000]` => longest trajectory starts at **77031** with **350 steps**.

## Complexity
* `trajectory(n)`: **O(s)** time, where `s` is the number of steps (O(1) space)
* `analyseInterval`: dynamic array `cache[0..b]` => **Space O(b)**. Each walk from `i` runs until it drops below `i`, and empirically the total is close to linear in `b`.
* **No proven worst-case bound** exists on `s`, because whether every trajectory even terminates is the open Collatz problem. That is why the analysis is stated in terms of the observed number of steps.
